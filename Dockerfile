FROM lganzzzo/alpine-cmake:latest

ADD . /service

WORKDIR /service/utility

RUN ./install-oatpp-modules.sh

WORKDIR /service/build

RUN cmake ..
RUN make

EXPOSE 9801 9801

ENTRYPOINT ["./my-project-exe"]
