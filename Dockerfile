FROM dea82/gcc-qt-docker:2.0.0
#
# INSTALL ZMQ
#
# Note: ZeroMQConfig.cmake.in is not available in release version but in master
# this file is necessary for generating the FindZeroMQ.cmake.
#
#
# INSTALL ZMQ C++ BINDINGS
#
# v4.2.2 of cpp bindings does not work with v4.2.2 of libzmq
#
RUN apk add --no-cache libtool git autoconf openssl ccache \
&& git clone --depth 1 --single-branch https://github.com/zeromq/libzmq.git && cd libzmq && mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=RELEASE .. && make -j2 install && cd .. && cd .. \
&& git clone --depth 1 --single-branch --branch v4.2.2 https://github.com/zeromq/cppzmq.git && cd cppzmq && mkdir build && cd build && cmake .. && make install
CMD bash