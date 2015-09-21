def expandPath(path):
	return Dir(path).get_abspath() + "/"
def getLibsPath():
	return [expandPath("libs")]
def getEigenPath():
	return "./eigen3-mirror/Eigen/".split(" ")
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

buildPath = expandPath("build")
srcPath = expandPath("src")

libs = ["glfw", "GLEW"]
src_files = Glob(srcPath + "*.cpp")

"""CXX=getCXX(), CXXFLAGS=getCXXFlags(), LINKFLAGS=getLinkFlags(), """
env = Environment(LIBS=libs, CPPPATH=getIncludePath(), LIBPATH=getLibsPath())
env.VariantDir(buildPath, srcPath)
env.Program("Terrian", src_files)
