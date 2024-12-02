WolframAlpha Mathematical Query Interface
This project is a Qt-based C++ GUI application that provides an intuitive interface to query mathematical expressions, solve problems, and visualize results using the WolframAlpha API. It features dropdown menus for different mathematical categories, a dynamic text editor for input, and integrated result display functionality.

Features
Interactive GUI: Users can input mathematical expressions and queries through a user-friendly interface.
Mathematical Categories:
Arithmetic: Perform basic operations such as addition, subtraction, multiplication, and division.
Algebra: Solve equations, factor, expand, and simplify expressions.
Trigonometry: Evaluate functions such as sine, cosine, tangent, and cotangent.
Calculus: Compute derivatives, integrals, summations, and limits.
Graphing: Generate and display graphs for equations and functions.
Symbols: Access commonly used symbols like 
π
π and \sqrt.
WolframAlpha Integration:
Sends user queries to the WolframAlpha API.
Displays plain text, graphical, and trigonometric results directly in the interface.
Dropdown Menus: Each mathematical category has its own dedicated menu for quick operation selection.
Setup and Installation
Prerequisites
Qt Framework: Ensure you have Qt 6.x or higher installed.
WolframAlpha API Key: Obtain an API key from the WolframAlpha Developer Portal.
Clone the Repository
git clone https://github.com/yourusername/wolframalpha-query-interface.git
cd wolframalpha-query-interface
Configure the Project
Open the .pro file in Qt Creator or your preferred Qt development environment.
Replace the appid in the sendSingleQuery function with your WolframAlpha API key.
Build and Run
Load the project in Qt Creator.
Configure your build kit (e.g., GCC, MSVC).
Compile and run the application.
Usage
Input: Enter your mathematical query in the text box or use the dropdown menus to build the query.
Submit: Click the Submit button to process your query.
View Results:
Plain text results are displayed in the Result Label.
Graphical results (if any) are fetched and displayed dynamically.
Example Queries

((5+(-20)*3^2))^2

expand (x^2+4x+16)(x^2+5x+15)

solve 2x=y, graph x^2+2x-5

Evaluate sin(π/4).

Code Overview
Main Components
MainWindow:

Initializes the UI and connects signals and slots.
Manages dropdown menus for mathematical operations.
API Integration:

Sends queries to the WolframAlpha API.
Parses and displays responses, including plain text and graphical results.
Dynamic Results:

Handles multiple response formats such as plain text, images, and LaTeX.
Key Methods
setupDropdownMenus: Configures dropdown menus for mathematical categories.
sendQueryToAPI: Sends the user's query to the WolframAlpha API.
processApiResponse: Parses the API response to extract results and display them.
Screenshots
Home Screen
(Add screenshots of the main window with menus and input fields.)

Query Results
(Add screenshots showing different types of results: plain text, graphs, etc.)

Dependencies
Qt 6.x
WolframAlpha API
Future Enhancements
Add support for step-by-step solutions.
Enhance error handling for invalid queries.
Improve graph visualization with interactive elements.
Add a profile for saving data.
Contribution
Contributions are welcome! Please fork the repository and submit a pull request.

License
This project is licensed under the MIT License. See the LICENSE file for details.

Contact
For any questions or feedback, feel free to contact Aidan at aidan@knut.com
