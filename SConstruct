def expandPath(path):
	return Dir(path).get_abspath() + "/"
def getLibsPath():
	return [expandPath("libs")]
def getEigenPath():
	return expandPath("./eigen3-mirror/").split(" ")
def getIncludePath():
	path = [expandPath("src/headers"), expandPath("include")]
	path.append(getEigenPath())

	return path
def getCXX():
	return "clang++"
def getCXXFlags():
	return "-std=c++11 -stdlib=libc++"
def getLinkFlags():
	return "-stdlib=libc++ -v"
def print_build_failures():
	from SCons.Script import GetBuildFailures
	for bf in GetBuildFailures():
		print "%s failed: %s" % (bf.node, bf.errstr)

buildPath = expandPath("build")
srcPath = expandPath("src")

libs = ["glfw", "GLEW", "GLU", "GL"]
src_files = Glob(srcPath + "*.cpp")

"""CXX=getCXX(), CXXFLAGS=getCXXFlags(), LINKFLAGS=getLinkFlags(), """
env = Environment(LIBS=libs, CPPPATH=getIncludePath(), LIBPATH=getLibsPath())
debug = ARGUMENTS.get('debug', 0)
if int(debug):
	    env.Append(CCFLAGS = '-g' + debug)
env.VariantDir(buildPath, srcPath)
env.Program("Terrian.bin", src_files)

print_build_failures()
