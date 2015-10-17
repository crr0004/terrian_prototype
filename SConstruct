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
buildPath = expandPath("build")
srcPath = expandPath("src")
testPath = expandPath("tests")

libs = ["glfw", "GLEW", "GLU", "GL"]
src_files = Glob(srcPath + "*.cpp")

env = Environment(LIBS=libs, CPPPATH=getIncludePath(), LIBPATH=getLibsPath())
debug = ARGUMENTS.get('debug', 0)
if int(debug):
	    env.Append(CCFLAGS = '-g' + debug)

tests = GetOption('tests')
if(tests):
	print src_files[0].get_abspath()
	src_files.remove(Glob(srcPath + "main.cpp")[0])
	print src_files[0].get_abspath()
	env.Append(CXXFLAGS = '-std=c++11')
	env.Program("Tests_Terrian.bin", Glob(testPath + "*.cpp") + src_files)
else:
	env.VariantDir(buildPath, srcPath)
	env.Program("Terrian.bin", src_files + Glob(srcPath + "main.cpp"))

	


print_build_failures()
