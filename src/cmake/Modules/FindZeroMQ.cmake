find_library(ZeroMQ_LIBRARY NAMES zmq libzmq HINTS $ENV{ZeroMQ_ROOT_DIR}/lib)

find_path(ZeroMQ_INCLUDE_DIR NAMES zmq.h HINTS $ENV{ZeroMQ_ROOT_DIR}/include)

function(extract_version_value value_name file_name value)
  file(STRINGS ${file_name} val REGEX "${value_name} .")
  string(FIND ${val} " " last REVERSE)
  string(SUBSTRING ${val} ${last} -1 val)
  string(STRIP ${val} val)
  set(${value} ${val} PARENT_SCOPE)
endfunction(extract_version_value)

extract_version_value("ZMQ_VERSION_MAJOR" ${ZeroMQ_INCLUDE_DIR}/zmq.h MAJOR)
extract_version_value("ZMQ_VERSION_MINOR" ${ZeroMQ_INCLUDE_DIR}/zmq.h MINOR)
extract_version_value("ZMQ_VERSION_PATCH" ${ZeroMQ_INCLUDE_DIR}/zmq.h PATCH)

set(ZeroMQ_VER "${MAJOR}.${MINOR}.${PATCH}")

set(ZeroMQ_FOUND ${ZEROMQ_FOUND})
set(ZeroMQ_INCLUDE_DIRS ${ZeroMQ_INCLUDE_DIR})
set(ZeroMQ_LIBRARIES ${ZeroMQ_LIBRARY})
set(ZeroMQ_VERSION ${ZeroMQ_VER})

mark_as_advanced(
  ZeroMQ_ROOT_DIR
  ZeroMQ_LIBRARY
  ZeroMQ_LIBRARY_DEBUG
  ZeroMQ_LIBRARY_RELEASE
  ZeroMQ_INCLUDE_DIR
  ZeroMQ_VERSION
)

message(STATUS "ZeroMQ version: ${ZeroMQ_VERSION}")
