require 'mkmf'
$CPPFLAGS << ' -std=c++11'
$defs << '-D RAKE_COMPILATION'
$LDFLAGS << ' -lPocoNet -lPocoFoundation -lprotobuf'
$INCFLAGS << ' -I${srcdir}/bot -I${srcdir}/world -I${srcdir}/network -I${srcdir}/network/messages -I${srcdir} '
create_makefile('botventure/botventure')
