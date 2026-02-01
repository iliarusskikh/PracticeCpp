//filesystem
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void processFile(const fs::path& filePath){
    //check if file exists
    if (!fs::exists(filePath)){
        std::cerr <<"File not found "<<"\n";
        return;
    }
    
    if(fs::is_regular_file(filePath)){
        std::cout <<"Size: "<<fs::file_size(filePath)<<" bytes"<<"\n";
    }
}


void listDirectory(const fs::path& dirPath){
    //check if directory exist
    if (!fs::exists(dirPath)) || !fs::is_directory(dirPath)){
        return;
    }
    
    //iterates through dir
    for (const auto& entry : fs::directory_iterator(dirPath))){
        std::cout <<entry.path().filename() <<"\n";
    }
}


void listFiles(const fs::path& dirPath){
    for(const auto& entry: fs::directory_iterator(dirPath)){
        std::cout << entry.path() <<"\n";
        if (entry.is_regular_file()){
            std::cout << " Size: "<<entry.file_size() <<" bytes"<<"\n";
        }
    }
}

void listFilesRecursive(const fs::path& dirPath){
    for(const auto& entry : fs::recursive_directory_iterator(dirPath)){
        //get indentation level based on depth
        int depth = entry.depth();
        std::string indent(depth*2,' ');
        std::cout <<ident << entry.path().filename()<<"\n";
    }
}


void safeFileOperation(){
    std::error_code ec;
    fs::path p = "nonexistent_file.txt";
    auto fileSize = fs::file_size(p, ec);
    if(ec){
        std::cout << ec.message() <<"\n";
    }
    
    try{
        fs::rename("old.txt","new.txt");
    }catch (const fs::filesystem_error& e){
        std::cerr<< e.what()<<"\n";
        
    }
}



int main()
{
    //std::filesystem::path file = "example.txt";
    fs::path file = "example.txt";
    
    if(fs::exists(file))
    {
        std::uintmax_t link_count = fs::hard_link_count(file);
        std::cout << "File "<< file << "Hard links " << link_count << std::endl;
        
        
    }
    
    
    
    //get current path
    fs::path currentPath = fs::current_path();
    std::cout << currentPath <<"\n";
    
    fs::directory_entry entry{myPath}; //represetns a directory entry (file/folder)
    for(autp& entry : fs::directory_iterator{dir})//iteractes through directory contents
    {
        
    }
    
    si::path filePath = "data/config.json";
    std::cout << "Filename: " <<filePath.filename <<"\n"
    std::cout << "Extension: " <<filePath.extension <<"\n"
    std::cout << "Parent: " <<filePath.parent_path <<"\n"
    
    //path concatenation: path1/path2
    //remove filename path.remove_filename();
    //replace extension: path.replace_extension()
    //check if absolute: path.is_absolute();
    //check if relative: path.is_relative();
    
    
    //is_directory(path) - checks if path is a directory
    //copy(from, to)
    //remove(path) - delete a file or empty directory
    //rename(old,new)
    
    //create_directory(path)
    //create_directoies(path) - directory and all parents
    //remove_all(path)
    //direcotry_iterator
    //recursive_directroy_iterator
    //current_path()
    
    
    //error handling
    //std::filesystem::filesystem_error
    //std::error_code
    //ec.value(), ec.message()
    
    
    
    
    return EXIT_SUCCESS;
}
