RUN sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"
RUN sudo apt update && sudo apt install -y build-essential cppcheck
RUN echo 'export CC=clang' >> /home/gitpod/.bashrc
RUN echo 'export CCX=clang++' >> /home/gitpod/.bashrc