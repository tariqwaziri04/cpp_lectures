FROM gitpod/workspace-c

RUN sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"
RUN sudo bash -c "$(curl -fsSL NONINTERACTIVE=1 https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
RUN sudo apt update && sudo apt install -y build-essential cppcheck
RUN echo 'export CC=clang' >> /home/gitpod/.bashrc
RUN echo 'export CCX=clang++' >> /home/gitpod/.bashrc
RUN brew install llvm
RUN echo 'export LDFLAGS="-L$(brew --prefix)/opt/llvm/lib -Wl,-rpath,$(brew --prefix)/opt/llvm/lib"'