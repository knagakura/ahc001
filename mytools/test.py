import subprocess
import os

def runShell(s):
    print(s)
    subprocess.run(s, shell=True)


# cppFile = input()
cppFile = "./src/a.cpp"
compile = "g++-9 -O2 -std=gnu++17 -Wall -Wextra -Wshadow -DDEBUG {}".format(cppFile)

print(runShell("pwd"))
inFile = "./tools/example.in"
outFile = "out.txt"

jikkou = "./a.out < {} > {}".format(inFile, outFile)

runShell(compile)

if(os.path.exists(outFile)):
    runShell("rum {}".format(outFile))

runShell(jikkou)
# root directoryからの相対パスで書く

runTest = "cd tools && cargo run --release --bin vis ../{} ../{} && open vis.html && cd ..".format(inFile, outFile)
runShell(runTest)