def expandPath(path):
	return Dir(path).get_abspath() + "/"
def getLibsPath():
	return [expandPath("libs")]
def getEigenPath():
	return "./eigen3-mirror/Eigen/".split(" ")
def getIncludePath():
	path = [expandPath("src/headers")]
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

libs = ["glfw"]
src_files = Glob(srcPath + "*.cpp")

VariantDir(buildPath, srcPath)
"""CXX=getCXX(), CXXFLAGS=getCXXFlags(), LINKFLAGS=getLinkFlags(), """
env = Environment(LIBS=libs, CPPPATH=getIncludePath(), LIBPATH=getLibsPath())
env.Program("Terrian", src_files)
