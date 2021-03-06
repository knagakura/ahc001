import subprocess
import os

def runShell(s):
    print(s)
    subprocess.run(s, shell=True)


# cppFile = input()
cppFile = "./src/a.cpp"
compile = "g++-9 -O2 -std=gnu++17 -Wall -Wextra -Wshadow {}".format(cppFile)
runShell(compile)
# inFile = "./tools/example.in"
# outFile = "out.txt"

os.makedirs("./tools/out", exist_ok=True)
for i in range(50):
    inFile = "tools/in/{}.txt".format(str(i).zfill(4))
    outFile = "tools/out/{}.txt".format(str(i).zfill(4))

    jikkou = "./a.out < {} > {}".format(inFile, outFile)

    if(os.path.exists(outFile)):
        runShell("rm {}".format(outFile))
    runShell(jikkou)
    # root directoryからの相対パスで書く

    runTest = "cd tools && cargo run --release --bin vis ../{} ../{} && open vis.html && cd ..".format(inFile, outFile)

    # runTest = "cd tools && cargo run --release --bin vis ../{} ../{} && cd ..".format(inFile, outFile)
    runShell(runTest)