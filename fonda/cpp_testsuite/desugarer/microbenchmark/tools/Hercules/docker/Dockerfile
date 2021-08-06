FROM openjdk:8
RUN mkdir /src
#install sbt
RUN echo "deb https://repo.scala-sbt.org/scalasbt/debian all main" | tee /etc/apt/sources.list.d/sbt.list
RUN echo "deb https://repo.scala-sbt.org/scalasbt/debian /" | tee /etc/apt/sources.list.d/sbt_old.list
RUN curl -sL "https://keyserver.ubuntu.com/pks/lookup?op=get&search=0x2EE0EA64E40A89B84B2DF73499E82A75642AC823" | apt-key add
RUN apt-get update && apt-get install sbt

#install typechef
RUN git clone https://github.com/aJanker/TypeChef.git /src/TypeChef && \
    cd /src/TypeChef && git checkout master && \
    sbt sbtVersion && ./publish.sh

#install hercules
RUN git clone https://github.com/joliebig/Hercules /src/Hercules
RUN cd /src/Hercules && ./mkrun.sh

WORKDIR /src/
