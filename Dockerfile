FROM ubuntu:18.04

RUN apt update
RUN apt install -y build-essential cmake libboost-exception-dev

COPY . /libusb2ax

WORKDIR /libusb2ax
RUN cmake .
RUN make -j4

CMD /libusb2ax/demo /dev/usb2ax
