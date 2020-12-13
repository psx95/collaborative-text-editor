//
// Created by tsnaik on 12/1/20.
//

#include <catch.hpp>
#include "VersionVector.hpp"

TEST_CASE("site counter can be incremented") {
  std::string site_id("32fc9593-2d1c-4aef-a0ed-3ed19be458a7");
  VersionVector version_vector(site_id);

  REQUIRE(version_vector.GetSiteCounter() == -1);

  SECTION("incrementing once") {
    version_vector.IncrementSiteCounter();
    REQUIRE(version_vector.GetSiteCounter() == 0);
  }

  SECTION("incrementing twice") {
    version_vector.IncrementSiteCounter();
    version_vector.IncrementSiteCounter();
    REQUIRE(version_vector.GetSiteCounter() == 1);
  }
}

TEST_CASE("version vector processes incoming actions") {
  std::string site_id("32fc9593-2d1c-4aef-a0ed-3ed19be458a7");
  std::string other_site_id("cfe26694-8e79-408f-9df3-ff6642ead6ad");
  VersionVector version_vector(site_id);
  std::string text("A");
  std::pair<long, std::string> pair = std::make_pair(0, site_id);
  std::vector<std::pair<long, std::string>> vector;
  vector.push_back(pair);

  REQUIRE(version_vector.GetSiteCounter() == -1);

  SECTION("insertion should apply immediately") {
    CRDTAction action(INSERT, other_site_id, 0, text, vector);

    std::vector<CRDTAction> apply = version_vector.ProcessRemoteAction(action, other_site_id, 0);
    REQUIRE(apply.size() == 1);
    REQUIRE(apply.at(0).Counter() == 0);
  }

  SECTION("out of order insertions should apply immediately") {
    CRDTAction action(INSERT, other_site_id, 1, text, vector);

    std::vector<CRDTAction> apply = version_vector.ProcessRemoteAction(action, other_site_id, 1);
    REQUIRE(apply.size() == 1);
    REQUIRE(apply.at(0).Counter() == 1);

    action = CRDTAction(INSERT, other_site_id, 0, text, vector);

    apply = version_vector.ProcessRemoteAction(action, other_site_id, 0);
    REQUIRE(apply.size() == 1);
    REQUIRE(apply.at(0).Counter() == 0);
  }

  SECTION("deletion without pending insert should apply immediately") {
    CRDTAction action(DELETE, other_site_id, 0, text, vector);

    std::vector<CRDTAction> apply = version_vector.ProcessRemoteAction(action, other_site_id, 0);
    REQUIRE(apply.size() == 1);
    REQUIRE(apply.at(0).Counter() == 0);
  }

  SECTION("insertion-deletion: both should apply immediately") {
    CRDTAction action(INSERT, other_site_id, 0, text, vector);

    std::vector<CRDTAction> apply = version_vector.ProcessRemoteAction(action, other_site_id, 0);
    REQUIRE(apply.size() == 1);
    REQUIRE(apply.at(0).Counter() == 0);

    action = CRDTAction(DELETE, other_site_id, 1, text, vector);

    apply = version_vector.ProcessRemoteAction(action, other_site_id, 1);
    REQUIRE(apply.size() == 1);
    REQUIRE(apply.at(0).Counter() == 1);
  }


  SECTION("in-order deletions without pending insert should apply immediately") {
    CRDTAction action(DELETE, other_site_id, 0, text, vector);

    std::vector<CRDTAction> apply = version_vector.ProcessRemoteAction(action, other_site_id, 0);
    REQUIRE(apply.size() == 1);
    REQUIRE(apply.at(0).Counter() == 0);

    action = CRDTAction(DELETE, other_site_id, 1, text, vector);

    apply = version_vector.ProcessRemoteAction(action, other_site_id, 1);
    REQUIRE(apply.size() == 1);
    REQUIRE(apply.at(0).Counter() == 1);
  }

  SECTION("out-of-order deletions without pending insert should NOT apply immediately") {
    CRDTAction action(DELETE, other_site_id, 1, text, vector);

    std::vector<CRDTAction> apply = version_vector.ProcessRemoteAction(action, other_site_id, 1);
    REQUIRE(apply.empty());

    action = CRDTAction(DELETE, other_site_id, 0, text, vector);

    apply = version_vector.ProcessRemoteAction(action, other_site_id, 0);
    REQUIRE(apply.size() == 2);
    REQUIRE(apply.at(0).Counter() == 0);
    REQUIRE(apply.at(1).Counter() == 1);
  }

  SECTION("deletion before insertion should go in buffer") {
    CRDTAction action(DELETE, other_site_id, 1, text, vector);

    std::vector<CRDTAction> apply = version_vector.ProcessRemoteAction(action, other_site_id, 1);
    REQUIRE(apply.empty());

    // the pending deletion should be applied now
    action = CRDTAction(INSERT, other_site_id, 0, text, vector);
    apply = version_vector.ProcessRemoteAction(action, other_site_id, 0);

    REQUIRE(apply.size() == 2);
    REQUIRE(apply.at(0).Counter() == 0);
    REQUIRE(apply.at(1).Counter() == 1);
  }

  SECTION("two deletions before insertion should go in buffer") {
    CRDTAction action(DELETE, other_site_id, 1, text, vector);

    std::vector<CRDTAction> apply = version_vector.ProcessRemoteAction(action, other_site_id, 1);
    REQUIRE(apply.empty());

    action = CRDTAction(DELETE, other_site_id, 2, text, vector);
    apply = version_vector.ProcessRemoteAction(action, other_site_id, 2);

    REQUIRE(apply.empty());

    // the pending deletion should be applied now
    action = CRDTAction(INSERT, other_site_id, 0, text, vector);
    apply = version_vector.ProcessRemoteAction(action, other_site_id, 0);

    REQUIRE(apply.size() == 3);
    REQUIRE(apply.at(0).Counter() == 0);
    REQUIRE(apply.at(1).Counter() == 1);
    REQUIRE(apply.at(2).Counter() == 2);
  }

  SECTION("insertion before two deletions before insertion") {
    CRDTAction action(INSERT, other_site_id, 1, text, vector);

    std::vector<CRDTAction> apply = version_vector.ProcessRemoteAction(action, other_site_id, 1);
    REQUIRE(apply.size() == 1);
    REQUIRE(apply.at(0).Counter() == 1);

    action = CRDTAction(DELETE, other_site_id, 3, text, vector);

    apply = version_vector.ProcessRemoteAction(action, other_site_id, 3);
    REQUIRE(apply.empty());

    action = CRDTAction(DELETE, other_site_id, 2, text, vector);
    apply = version_vector.ProcessRemoteAction(action, other_site_id, 2);

    REQUIRE(apply.empty());

    // the pending deletion should be applied now
    action = CRDTAction(INSERT, other_site_id, 0, text, vector);
    apply = version_vector.ProcessRemoteAction(action, other_site_id, 0);

    REQUIRE(apply.size() == 3);
    REQUIRE(apply.at(0).Counter() == 0);
    REQUIRE(apply.at(1).Counter() == 2);
    REQUIRE(apply.at(2).Counter() == 3);
  }
}

TEST_CASE("version vector ignores duplicate actions") {
  std::string site_id("32fc9593-2d1c-4aef-a0ed-3ed19be458a7");
  std::string other_site_id("cfe26694-8e79-408f-9df3-ff6642ead6ad");
  VersionVector version_vector(site_id);
  std::string text("A");
  std::pair<long, std::string> pair = std::make_pair(0, site_id);
  std::vector<std::pair<long, std::string>> vector;
  vector.push_back(pair);

  REQUIRE(version_vector.GetSiteCounter() == -1);

  SECTION("duplicate inserts should get ignored") {
    CRDTAction action(INSERT, other_site_id, 0, text, vector);

    std::vector<CRDTAction> apply = version_vector.ProcessRemoteAction(action, other_site_id, 0);
    REQUIRE(apply.size() == 1);
    REQUIRE(apply.at(0).Counter() == 0);

    action = CRDTAction(INSERT, other_site_id, 0, text, vector);

    apply = version_vector.ProcessRemoteAction(action, other_site_id, 0);
    REQUIRE(apply.empty());
  }

  SECTION("duplicate deletes should get ignored") {
    CRDTAction action(DELETE, other_site_id, 0, text, vector);

    std::vector<CRDTAction> apply = version_vector.ProcessRemoteAction(action, other_site_id, 0);
    REQUIRE(apply.size() == 1);
    REQUIRE(apply.at(0).Counter() == 0);

    action = CRDTAction(DELETE, other_site_id, 0, text, vector);

    apply = version_vector.ProcessRemoteAction(action, other_site_id, 0);
    REQUIRE(apply.empty());
  }
}
