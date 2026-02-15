# Folder Organizer

A high-performance **Folder Organizer and Duplicate File Cleaner** built using **C++** for fast file system operations and **Python (Tkinter)** for a simple graphical user interface.

The tool scans a selected folder, safely detects duplicate files, asks for user confirmation before deletion, and then organizes files into categorized folders such as **Images**, **Videos**, **Documents**, **Music**, and **Archives**.

> A ready-to-use Windows executable is available in the **Releases** section.

---

## Features

- Automatically organizes files by type  
- Detects duplicate files using file size + hashing  
- Asks for confirmation before deleting any file  
- Prevents filename conflicts using smart renaming  
- Simple GUI (no terminal interaction required)  
- Fast performance using C++ `std::filesystem`

---

## Technologies Used

- **C++17**
  - `std::filesystem`
  - `unordered_map`, `unordered_set`
- **Python 3**
  - `tkinter`
  - `subprocess`
- **GitHub Releases**
  - Executable distribution

---

## How It Works

1. The program scans the selected folder recursively.
2. Files are grouped by **file size** to reduce unnecessary comparisons.
3. Files with matching sizes are **hashed and compared**.
4. When duplicate files are found:
   - The user is asked to confirm deletion (Yes / No).
5. Remaining files are organized into:
   - Images  
   - Videos  
   - Documents  
   - Music  
   - Archives
6. If a filename conflict occurs, the program renames the file safely.

---

## How to Use

1. Download the latest release from the **Releases** section.
2. Make sure `fs-organizer.exe` is in the same directory as **Folder Organizer.exe**.
3. Run the application: Folder Organizer.exe
4. Select the folder you want to organize.
5. Confirm deletion when duplicate files are detected.
6. The folder will be cleaned and organized automatically.

---

## Screenshots

### Folder Before
<img width="1166" height="662" src="https://github.com/user-attachments/assets/8427c18d-3a8c-46b9-bd0d-9d24db9099ad" />

---

### Program Running
<img width="991" height="630" src="https://github.com/user-attachments/assets/d7838fcc-8cc0-4865-a116-c66f6fc549b2" />
<img width="546" height="275" src="https://github.com/user-attachments/assets/3e401910-81b7-40ea-a798-f08a1468a821" />
<img width="543" height="286" src="https://github.com/user-attachments/assets/7e8efcd5-52da-4c3a-8d43-3101df7fcfcb" />

---

### Finished Message
<img width="378" height="245" src="https://github.com/user-attachments/assets/e01f6edf-3c63-4f72-ae93-f40275acfb0b" />

---

### Folder After
<img width="1144" height="552" src="https://github.com/user-attachments/assets/b299d5e2-1391-4275-84e1-dd585904b76e" />

---

## Future Improvements

- Use a stronger hashing algorithm to reduce collisions  
- Add a progress indicator for large folders  
- Allow previewing duplicate files before deletion  
- Support custom file categories  

---

## Author

**Youssef**

---

## Feedback

If you have any suggestions, improvements, or recommendations, feel free to open an issue or submit a pull request.  
All feedback is appreciated.
