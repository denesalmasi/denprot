AM_CXXFLAGS = -std=c++0x -Werror -pedantic-errors -I../inc $(DPTCPP_CFLAGS) $(BOOST_CPPFLAGS) -DDEBUG -O3
DPTCPP_LIBRARY_VERSION=1:1:0

lib_LTLIBRARIES = libdptcpp-0.1.la
libdptcpp_0_1_la_SOURCES = Exception.cpp Debug.cpp Id.cpp \
	AsyncWrap.cpp InvalidPropertyException.cpp \
	PropertyCollection.cpp PropertyReactor.cpp SingleAcceptContext.cpp \
	TabledParseContext.cpp TerminalContext.cpp XmlParser.cpp \
	XmlParserInner.cpp
libdptcpp_0_1_la_LDFLAGS = version-info $(DPTCPP_LIBRARY_VERSION) $(DPTCPP_LIBS) $(BOOST_SYSTEM_LDFLAGS) $(BOOST_THREAD_LDFLAGS)
libdptcpp_0_1_la_LIBS = $(BOOST_SYSTEM_LIBS) $(BOOST_THREAD_LDFLAGS)
