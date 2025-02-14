

// includes

#include <string>
#include <vector>
#include <unordered_map>
#include "../include/json.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>


// aliases

using std::string, std::vector, std::unordered_map;
using json = nlohmann::json;
using std::cout, std::ofstream, std::ifstream, std::stringstream;
namespace fs = std::filesystem;


// constants

const string version = "0.1.1";
const string versionDate = "14 Feb 2025";


// main

int main(int argc, char* argv[]) {
    
    // check option argument
    if(argc < 2) {
        cout << "You need to provide an option argument. Use \"acr -h\" to get help.";
        return 1;
    }
    if(argv[1][0] != '-') {
        cout << "Options need to start with \"-\".";
        return 1;
    }
    
    // options
    switch(argv[1][1]) {
    
        // -h - help
        case 'h': {
            cout << "\n"
                    "  \033[1mAcrylic packager help\033[0m\n"
                    "\n"
                    "  \033[1m-h\033[0m\n"
                    "    Get help options\n"
                    "    acr -h\n"
                    "  \033[1m-v\033[0m\n"
                    "    Get the version of the Acrylic packager\n"
                    "    acr -v\n"
                    "  \033[1m-p\033[0m\n"
                    "    Package a folder into an .acr package\n"
                    "    acr -p [folder] [output package]\n"
                    "  \033[1m-e\033[0m\n"
                    "    Extract an .acr package into a folder\n"
                    "    acr -e [package] [output folder]\n"
                    "  Note that the [output] arguments are optional.\n";
            break;
        }
        
        // -v - version
        case 'v': {
            cout << "\n"
                    "  \033[1mAcrylic packager\033[0m\n"
                    "  Version " << version << " (" << versionDate << ")\n"
                    "  https://github.com/acrylic-os/packager\n"
                    "  MIT license, (c) anpang54\n";
            break;
        }
        
        // -p - package
        case 'p': {
        
            // check input argument
            if(argc < 3) {
                cout << "You need to provide at least the input argument. Use \"acr -h\" to get help.";
                return 1;
            }
            
            // get output path
            string output;
            if(argc == 3) {
                output = string(argv[2]).append(".acr");
            } else {
                output = string(argv[3]).append(".acr");
            }
            
            // recursively get and read files in the directory
            unordered_map<string, string> files;
            string path;
            for(fs::recursive_directory_iterator i(argv[2]), end; i != end; ++i) {
                path = i->path();
                if(!fs::is_directory(path)) {
                    ifstream stream(path);
                    stringstream buffer;
                    buffer << stream.rdbuf();
                    files[path.substr(path.find('/') + 1)] = buffer.str();
                }
            }
            
            // print
            json jsonized = files;
            ofstream file(output);
            file << jsonized.dump();
            file.close();
            
            cout << "Succesfully packaged folder \"" << argv[2] << "\" into package \"" << output << "\".";
            break;
        
        }
        
        // -e - extract
        case 'e': {
        
            // check input argument
            if(argc < 3) {
                cout << "You need to provide at least the input argument. Use \"acr -h\" to get help.";
                return 1;
            }
            
            // get output path
            string output;
            if(argc == 3) {
                output = argv[2];
            } else {
                output = argv[3];
            }
            
            // read and parse the file
            ifstream stream(argv[2]);
            stringstream buffer;
            buffer << stream.rdbuf();
            unordered_map<string, string> files = json::parse(buffer.str());
            
            // extract it
            fs::create_directory(output);
            string filePath;
            for(auto& [path, content]: files) {
            
                filePath = output + "/" + path;
                
                // make directories if needed
                vector<string> splitted;
                stringstream stream(path);
                string item;
                while(getline(stream, item, '/')) {
                    splitted.push_back(item);
                }
                splitted.pop_back();    // remove the filename at the end
                string fullPath = "";
                for(string& item: splitted) {
                    fullPath.append(item);
                    if(!fs::exists(output + "/" + fullPath)) {                        fs::create_directory(output + "/" + fullPath);
                    }
                    fullPath.append("/");
                }

                // put the file
                ofstream file(filePath);
                file << content;
                file.close();
            }
            
            cout << "Succesfully extracted page \"" << argv[2] << "\" into folder \"" << output << "\".";
           
            break;
            
        }
        
        // default
        default: {
            cout << "Invalid option \"" << argv[1] << "\". Use \"acr -h\" to get help.";
            return 1;
        }
        
    }
    
    return 0;
    
}

