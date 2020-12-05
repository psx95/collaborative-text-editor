//
// Created by psx95 on 11/15/20.
//

#ifndef COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORWINDOW_HPP_
#define COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORWINDOW_HPP_
#include <SFML/Graphics.hpp>
#include "EditorView.hpp"
#include "InputHandler.hpp"
#include "EditorCallbacks.hpp"

/*!
 * @brief This class maintains the event loop and is responsible for managing the visual window that is present on
 * screen.
 */
class EditorWindow {
 private:
  sf::RenderWindow *editor_window{}; // The SFML render window which represents a GUI window that allows drawing
  EditorView *editor_view{}; // The view that is drawn on the render window.
  EditorContent *editor_content{}; // The content that is represented on the view.
  TextFileContent *text_file_content{}; // The actual text content that is represented by the editor content.
  InputHandler *input_handler{}; // The InputHandler object that handles the keyboard and mouse input from user.
  sf::Color background_color{}; // The background color for the RenderWindow.

  void InitializeEditorWindow(std::string &site_id); // Sets up all objects that are required prior to beginning event loop.
  void UpdateEvents(); // This method polls for any new events made by the user.
  void DrawUpdates(); // This method draws the changes which were introduced as a result of user events

 public:
  /*!
   * @brief Public constructor for the EditorWindow.
   * @param background_color The background color for the window.
   * @param site_id The unique ID for the client.
   */
  explicit EditorWindow(sf::Color background_color, std::string &site_id);

  /*!
   * @brief This method starts the main event loop that controls the program flow on the main thread.
   * @details This starts an infinite loop which will keep on running unless the user manually closes the applicaiton.
   */
  void StartEventLoop();

  /*!
   * @brief This method is used to close the GUI window and consecutively stop the program.
   * @details This method should be used to indicate the user wants to exit the application.
   */
  void CloseWindow();

  /*!
   * @brief This method is used to set EditorCallbacks for EditorContent.
   * @param editor_callbacks A pointer to the EditorCallbacks objects.
   */
  void SetEditorCallbacks(EditorCallbacks *editor_callbacks);

  void InsertText(std::string &text, int index);

  void DeleteTextFrom(int index, int num_chars = 1);

  /*!
   * @brief Custom destructor for the EditorWindow. Should be used to reclaim any manually allocated memory.
   */
  ~EditorWindow();
};

#endif //COLLABORATIVE_TEXT_EDITOR_SRC_EDITOR_EDITORWINDOW_HPP_
