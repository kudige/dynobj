AR = '/usr/bin/ar'
ARFLAGS = 'rcs'
CCFLAGS = ['-g']
CCFLAGS_MACBUNDLE = ['-fPIC']
CCFLAGS_NODE = ['-D_LARGEFILE_SOURCE', '-D_FILE_OFFSET_BITS=64']
CC_VERSION = ('4', '2', '1')
COMPILER_CXX = 'g++'
CPP = '/usr/bin/cpp'
CPPFLAGS_NODE = ['-D_GNU_SOURCE', '-DEV_MULTIPLICITY=0']
CPPPATH_NODE = '/usr/local/include/node'
CPPPATH_ST = '-I%s'
CXX = ['/usr/bin/g++']
CXXDEFINES_ST = '-D%s'
CXXFLAGS = ['-g']
CXXFLAGS_DEBUG = ['-g']
CXXFLAGS_NODE = ['-D_LARGEFILE_SOURCE', '-D_FILE_OFFSET_BITS=64']
CXXFLAGS_RELEASE = ['-O2']
CXXLNK_SRC_F = ''
CXXLNK_TGT_F = ['-o', '']
CXX_NAME = 'gcc'
CXX_SRC_F = ''
CXX_TGT_F = ['-c', '-o', '']
DEST_CPU = 'x86_64'
DEST_OS = 'darwin'
FULLSTATIC_MARKER = '-static'
LIBDIR = '/Users/chandan/.node_libraries'
LIBPATH_NODE = '/usr/local/lib'
LIBPATH_ST = '-L%s'
LIB_ST = '-l%s'
LINKFLAGS_MACBUNDLE = ['-bundle', '-undefined', 'dynamic_lookup']
LINK_CXX = ['/usr/bin/g++']
NODE_PATH = '/Users/chandan/.node_libraries'
PREFIX = '/usr/local'
PREFIX_NODE = '/usr/local'
RANLIB = '/usr/bin/ranlib'
RPATH_ST = '-Wl,-rpath,%s'
SHLIB_MARKER = ''
SONAME_ST = ''
STATICLIBPATH_ST = '-L%s'
STATICLIB_MARKER = ''
STATICLIB_ST = '-l%s'
macbundle_PATTERN = '%s.bundle'
program_PATTERN = '%s'
shlib_CXXFLAGS = ['-fPIC', '-compatibility_version', '1', '-current_version', '1']
shlib_LINKFLAGS = ['-dynamiclib']
shlib_PATTERN = 'lib%s.dylib'
staticlib_LINKFLAGS = []
staticlib_PATTERN = 'lib%s.a'
