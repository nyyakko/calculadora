import os
import sys

DIRECTORY = os.getcwd()
REPLACED  = sys.argv[1]
WILDCARD  = '!PROJECT_TEMPLATE!'

def replace_file_wildcard(path, name):
    if os.path.basename(path) == 'setup.py': return

    with open(path, 'r') as file:
        data = file.read()
        data = data.replace(WILDCARD, REPLACED)
    with open(path, 'w') as file:
        file.write(data)

def replace_folder_wildcard(path, name):
    if os.path.basename(path) == WILDCARD:
        folderName = os.path.join(os.path.dirname(path), REPLACED)
        os.rename(path, folderName)

def replace_project_wildcards(directory, name):
    for filename in os.listdir(directory):
        path = os.path.join(directory, filename)

        if os.path.basename(path) == ".git": continue

        if os.path.isfile(path): replace_file_wildcard(path, name)

        if os.path.isdir(path):
            replace_project_wildcards(path, name)
            replace_folder_wildcard(path, name)

replace_project_wildcards(DIRECTORY, REPLACED)
