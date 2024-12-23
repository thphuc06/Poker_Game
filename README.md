🎲 Poker_Game ♠️♥️
👥 Team Members:
Nguyễn Thành Trung
Trần Cao Danh
Trần Hoàng Phúc
🎓 Education:
Ho Chi Minh University of Science | DH Khoa Học Tự Nhiên, ĐHQG TPHCM

📖 Project Description:
This project was developed as part of our first-year first semester coursework.
It simulates a Poker Game with multiple playing modes, designed using C++ and SFML.

🚀 Key Features:
Support for multiple Poker game types: Hold'Em, Three-Card Poker, etc.
User-friendly console interface.
Modular and scalable code structure.
Powered by SFML (Simple and Fast Multimedia Library) for enhanced graphical support.
🎥 Video Instruction:
Watch the Demo Video Here

📑 Detailed Report:
Read the Full Report Here

🛠️ Prerequisites
Before running the project, make sure you have the following installed on your system:

📦 1. SFML Library
On Ubuntu/Debian:

bash
Sao chép mã
sudo apt-get update
sudo apt-get install libsfml-dev
On macOS (Using Homebrew):

bash
Sao chép mã
brew install sfml
On Windows:

Download SFML from the official website.
Extract the downloaded files.
Set up the SFML environment in your compiler (e.g., Visual Studio or MinGW).
Add SFML's bin folder to your system's PATH variable.
🖥️ 2. C++ Compiler
Linux/macOS: GCC (e.g., g++ 11.2.0 or later)
Windows: MinGW or Visual Studio Build Tools
⚙️ 3. Build System (Optional)
Linux/macOS: Make (make)
Windows: Command Prompt (cmd) or PowerShell
⚙️ Installation Instructions
Follow these steps to clone, build, and run the project:

1. Clone the Repository:
Use the following command to clone the repository:

bash
Sao chép mã
git clone https://github.com/thphuc06/Poker_Game.git
2. Navigate to the Project Directory:
Move into the project folder:

bash
Sao chép mã
cd Poker_Game
3. Compile the Code with SFML:
On Linux/macOS:

bash
Sao chép mã
g++ -o poker_game fullmain.cpp HoldEm.cpp Normal.cpp PVE.cpp ThreeCards.cpp -lsfml-graphics -lsfml-window -lsfml-system -std=c++11
On Windows (Using MinGW):

cmd
Sao chép mã
g++ -o poker_game fullmain.cpp HoldEm.cpp Normal.cpp PVE.cpp ThreeCards.cpp -I path\to\SFML\include -L path\to\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system -std=c++11
4. Run the Program:
Execute the compiled file:

bash
Sao chép mã
./poker_game
5. Enjoy the Game:
Follow the on-screen instructions to start playing.

🛠️ Troubleshooting
If you encounter any issues during setup or compilation, try the following:

Verify SFML Installation:
Ensure SFML is installed properly and library paths are correctly set.

Check Compiler Version:
Ensure you're using a compiler that supports C++11 or later.

Library Linking Issue:
Double-check SFML libraries in your compile command.

Documentation Reference:
Consult the official SFML Documentation.

Open an Issue:
If you still face problems, please open an issue on this repository, and we’ll assist you.

📊 Technologies Used
Programming Language: C++
Library: SFML (Simple and Fast Multimedia Library)
Tools: Visual Studio Code, GCC, MinGW
Version Control: Git & GitHub
📝 Future Improvements
Add multiplayer functionality.
Improve graphical user interface with SFML.
Include detailed statistics and player records.
🤝 Contributing
We welcome contributions!

Fork the repository.
Create a new branch.
Make your changes and test them.
Submit a pull request.
📬 Contact Information
Nguyễn Thành Trung: Email
Trần Cao Danh: Email
Trần Hoàng Phúc: Email
⭐ Acknowledgments
Thanks to SFML Community for their amazing library.
Our mentors and professors for guidance throughout this project.
🎯 Final Notes
If you enjoyed this project, don’t forget to ⭐ star this repository!

Feel free to share your thoughts or report any bugs in the Issues section.

✅ How to Update Your README.md
Open your repository on GitHub.
Click on README.md → Edit.
Paste the content above.
Click Commit Changes.
✅ Push Changes (If Using Terminal):
bash
Sao chép mã
git add README.md
git commit -m "Update README with SFML setup and troubleshooting"
git push
