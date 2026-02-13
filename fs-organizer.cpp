#include <iostream>
#include <filesystem>
#include <string>
#include <unordered_set>
#include <algorithm>
using namespace std;
namespace fs = std::filesystem;

int main()
{
    string folderPath;
    
    unordered_set <string> imageExtensions = 
    {".png", ".jpg", ".jpeg", ".bmp", ".gif", ".tiff", ".webp"};
    unordered_set<string> videoExtensions =
    {".mp4", ".avi", ".mkv", ".mov", ".flv", ".wmv", ".webm"};
    unordered_set<string> documentExtensions =
    {".pdf", ".doc", ".docx", ".txt", ".ppt", ".pptx", ".xls", ".xlsx"};
    unordered_set<string> musicExtensions =
    {".mp3", ".wav", ".flac", ".aac", ".ogg", ".wma"};
    unordered_set<string> archiveExtensions =
    {".zip", ".rar", ".7z", ".tar", ".gz"};

    while (true)
    {
        cout << "Enter A Folder Path: ";
        getline (cin, folderPath);

        if (fs::exists(folderPath) && fs::is_directory(folderPath))
        {
            break;
        }else
        {
            cout << "Invalid Folder Path, Try Again!" << endl;
        }
    }
    for (const auto& entry : fs::recursive_directory_iterator(folderPath))
    {
        if (!fs::is_regular_file(entry))
        {
            continue;
        }
        auto ext = entry.path().extension().string();
        transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
        auto fileName = entry.path().filename().string();
        auto filePath = entry.path().string();
        string fileDest;

        if (imageExtensions.count(ext))
        {
            fs::create_directories(folderPath + "/Images");
            fileDest = folderPath + "/Images/" + fileName;
            fs::rename(filePath, fileDest);

        }else if (videoExtensions.count(ext))
        {
            fs::create_directories(folderPath + "/Videos");
            fileDest = folderPath + "/Videos/" + fileName;
            fs::rename(filePath, fileDest);

        }else if (documentExtensions.count(ext))
        {
            fs::create_directories(folderPath + "/Documents");
            fileDest = folderPath + "/Documents/" + fileName;
            fs::rename(filePath, fileDest);

        }else if (archiveExtensions.count(ext))
        {
            fs::create_directories(folderPath + "/Archives");
            fileDest = folderPath + "/Archives/" + fileName;
            fs::rename(filePath, fileDest);

        }else if (musicExtensions.count(ext))
        {
            fs::create_directories(folderPath + "/Music");
            fileDest = folderPath + "/Music/" + fileName;
            fs::rename(filePath, fileDest);
        }
    }
    cout << "Folder Cleaning Completed!" << endl;
    return 0;
}