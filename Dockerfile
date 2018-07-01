# daemon runs in the background
# run something like tail /var/log/monkeytipsd/current to see the status
# be sure to run with volumes, ie:
# docker run -v $(pwd)/monkeytipsd:/var/lib/monkeytipsd -v $(pwd)/wallet:/home/monkeytips --rm -ti monkeytips:0.2.2
ARG base_image_version=0.10.0
FROM phusion/baseimage:$base_image_version

ADD https://github.com/just-containers/s6-overlay/releases/download/v1.21.2.2/s6-overlay-amd64.tar.gz /tmp/
RUN tar xzf /tmp/s6-overlay-amd64.tar.gz -C /

ADD https://github.com/just-containers/socklog-overlay/releases/download/v2.1.0-0/socklog-overlay-amd64.tar.gz /tmp/
RUN tar xzf /tmp/socklog-overlay-amd64.tar.gz -C /

ARG MONKEYTIPS_BRANCH=master
ENV MONKEYTIPS_BRANCH=${MONKEYTIPS_BRANCH}

# install build dependencies
# checkout the latest tag
# build and install
RUN apt-get update && \
    apt-get install -y \
      build-essential \
      python-dev \
      gcc-4.9 \
      g++-4.9 \
      git cmake \
      libboost1.58-all-dev \
      librocksdb-dev && \
    git clone https://github.com/monkeytips/monkeytips.git /src/monkeytips && \
    cd /src/monkeytips && \
    git checkout $MONKEYTIPS_BRANCH && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_CXX_FLAGS="-g0 -Os -fPIC -std=gnu++11" .. && \
    make -j$(nproc) && \
    mkdir -p /usr/local/bin && \
    cp src/monkeytipsd /usr/local/bin/monkeytipsd && \
    cp src/walletd /usr/local/bin/walletd && \
    cp src/zedwallet /usr/local/bin/zedwallet && \
    cp src/miner /usr/local/bin/miner && \
    strip /usr/local/bin/monkeytipsd && \
    strip /usr/local/bin/walletd && \
    strip /usr/local/bin/zedwallet && \
    strip /usr/local/bin/miner && \
    cd / && \
    rm -rf /src/monkeytips && \
    apt-get remove -y build-essential python-dev gcc-4.9 g++-4.9 git cmake libboost1.58-all-dev librocksdb-dev && \
    apt-get autoremove -y && \
    apt-get install -y  \
      libboost-system1.58.0 \
      libboost-filesystem1.58.0 \
      libboost-thread1.58.0 \
      libboost-date-time1.58.0 \
      libboost-chrono1.58.0 \
      libboost-regex1.58.0 \
      libboost-serialization1.58.0 \
      libboost-program-options1.58.0 \
      libicu55

# setup the monkeytipsd service
RUN useradd -r -s /usr/sbin/nologin -m -d /var/lib/monkeytipsd monkeytipsd && \
    useradd -s /bin/bash -m -d /home/monkeytips monkeytips && \
    mkdir -p /etc/services.d/monkeytipsd/log && \
    mkdir -p /var/log/monkeytipsd && \
    echo "#!/usr/bin/execlineb" > /etc/services.d/monkeytipsd/run && \
    echo "fdmove -c 2 1" >> /etc/services.d/monkeytipsd/run && \
    echo "cd /var/lib/monkeytipsd" >> /etc/services.d/monkeytipsd/run && \
    echo "export HOME /var/lib/monkeytipsd" >> /etc/services.d/monkeytipsd/run && \
    echo "s6-setuidgid monkeytipsd /usr/local/bin/monkeytipsd" >> /etc/services.d/monkeytipsd/run && \
    chmod +x /etc/services.d/monkeytipsd/run && \
    chown nobody:nogroup /var/log/monkeytipsd && \
    echo "#!/usr/bin/execlineb" > /etc/services.d/monkeytipsd/log/run && \
    echo "s6-setuidgid nobody" >> /etc/services.d/monkeytipsd/log/run && \
    echo "s6-log -bp -- n20 s1000000 /var/log/monkeytipsd" >> /etc/services.d/monkeytipsd/log/run && \
    chmod +x /etc/services.d/monkeytipsd/log/run && \
    echo "/var/lib/monkeytipsd true monkeytipsd 0644 0755" > /etc/fix-attrs.d/monkeytipsd-home && \
    echo "/home/monkeytips true monkeytips 0644 0755" > /etc/fix-attrs.d/monkeytips-home && \
    echo "/var/log/monkeytipsd true nobody 0644 0755" > /etc/fix-attrs.d/monkeytipsd-logs

VOLUME ["/var/lib/monkeytipsd", "/home/monkeytips","/var/log/monkeytipsd"]

ENTRYPOINT ["/init"]
CMD ["/usr/bin/execlineb", "-P", "-c", "emptyenv cd /home/monkeytips export HOME /home/monkeytips s6-setuidgid monkeytips /bin/bash"]
