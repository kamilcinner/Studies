import os

os.system('./mvnw generate-resources')

os.system('touch npm')
with open('./npm', 'w') as f:
    f.write('#!/bin/sh\ncd $(dirname $0)\nPATH="$PWD/node/":$PATH\nnode "node/node_modules/npm/bin/npm-cli.js" "$@"')
    f.close()
os.system('chmod +x npm')
os.system('./npm install @angular/cli')

os.system('touch ng')
with open('./ng', 'w') as f:
    f.write('#!/bin/sh\ncd $(dirname $0)\nPATH="$PWD/node/":$PATH\nnode "node/node_modules/npm/bin/npm-cli.js" "$@"')
    f.close()
os.system('#!/bin/sh\ncd $(dirname $0)\nPATH="$PWD/node/":"$PWD":$PATH\nnode_modules/@angular/cli/bin/ng "$@"')
os.system('chmod +x ng')
os.system('./ng --version')

os.system('./ng new client')
os.system('cat client/.gitignore >> .gitignore')
os.system('rm -rf client/node* client/.gitignore client/.git')
os.system('sed -i -e "s/node_/anode/" .gitignore')
os.system('cp -rf client/* .')
os.system('cp client/.??* .')
os.system('rm -rf client')
os.system('sed -i -e "s,dist/client,target/classes/static," angular.json')
os.system('echo "now return to site"')
