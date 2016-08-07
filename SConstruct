def expandPath(path):
    return Dir(path).get_abspath() + "/"
def getLibsPath():
    return [expandPath("libs")]
def getIncludePath():
    path = [expandPath("src/headers"), expandPath("include")]
    return path
def getCXX():
    return "clang++"
def getCXXFlags():
    return "-std=c++11"
def getLinkFlags():
    return "-stdlib=libc++ -v"
def print_build_failures():
    from SCons.Script import GetBuildFailures
    for bf in GetBuildFailures():
        print "%s failed: %s" % (bf.node, bf.errstr)

AddOption('--tests',
        action='store_true',
        dest='tests')

AddOption('--luatests', action='store_true', dest='luatests')

buildPath = expandPath("build")
srcPath = expandPath("src/src")
testPath = expandPath("tests")
luatestsPath = expandPath("luatests")

libs = ["glfw", "GLEW", "GLU", "GL"]
src_files = Glob(srcPath + "*.cpp")

env = Environment(LIBS=libs, CPPPATH=getIncludePath(), LIBPATH=getLibsPath())
debug = ARGUMENTS.get('debug', 0)
if int(debug):
    env.Append(CCFLAGS = '-g' + debug + ' -Wall')

tests = GetOption('tests')
luatests = GetOption('luatests')
if(tests == True):
    env.Append(CXXFLAGS = '-std=c++11')
    env.Program("Tests_Terrian.bin", Glob(testPath + "*.cpp") + src_files)
elif(luatests == True):
    env.Append(LIBS='lua')
    env.Program("LuaTests.bin", Glob(luatestsPath + "*.cpp"))
else:
    src_files += Glob("src/main.cpp")
    env.VariantDir(buildPath, srcPath)
    env.Program("Terrian.bin", src_files)

print_build_failures()
