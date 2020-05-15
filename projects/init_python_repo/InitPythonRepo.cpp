#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;

void split_by_delimiter(string const &str, const char delimiter, vector<string> &out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delimiter, end)) != string::npos)
    {
        end = str.find(delimiter, start);
        out.push_back(str.substr(start, end - start));
    }
}

string lowercase_name(string const &str)
{
    string lowercased = "";
    for (size_t i = 0; i < str.length(); i++)
    {
        lowercased += tolower(str[i]);
    }
    return lowercased;
}

int main(int argc, char const *argv[])
{

    string current_dir = getenv("PWD");

    // Get last part of path as name
    vector<string> out;
    split_by_delimiter(current_dir, '/', out);
    string name = out.back();

    cout << "Intialize python repository at: " << current_dir << endl;
    cout << "Python Repository Name: " << name << endl;
    cout << "==========================================" << endl;

 
    // Format string to lower case
    string lowercased_name = lowercase_name(name);

    // Get directory of templates
    string template_folder = getenv("SCRIPTS");
    template_folder += +"/../templates/python/.";

    // Copy all templates into working directory
    cout << "Copy template files..." << endl;
    string copy_cmd = "cp -R ";
    copy_cmd += template_folder + " " + current_dir;
    system(copy_cmd.c_str());

    // Replace placeholders with actual values
    string replace_cmd = "sed -i -E 's/NAME/" + name + "/g' setup.py";
    system(replace_cmd.c_str());
    replace_cmd = "sed -i -E 's/INCLUDE/" + lowercased_name + "/g' setup.py";
    system(replace_cmd.c_str());

    // Create remaining files
    cout << "Create remaining files..." << endl;

    system("touch requirements.txt");
    system("touch README.md");

    string text = "echo # " + name + "> README.md";
    system(text.c_str());

    cout << "Create directories..." << endl;

    vector<string> dirs;
    dirs.push_back("tests");
    dirs.push_back("docs");
    dirs.push_back(lowercased_name);

    for (size_t i = 0; i < dirs.size(); i++)
    {
        string cmd = "mkdir " + dirs[i];
        system(cmd.c_str());
    }

    string cmd = "touch " + lowercased_name + "/__init__.py";
    system(cmd.c_str());

    cout << "Create virtualenv '.venv'" << endl;
    system("python -m venv .venv");

    cout << "Commit setup files as first commit" << endl;
    system("git init");
    system("git add .");

    system("git commit -m \"Initial setup commit\"");

    cout << endl
         << "Please add a remote repository and 'git push'" << endl
         << endl;

    return 0;
}
