FROM gitpod/workspace-c

# RUN sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"
# RUN sudo echo | sudo bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# RUN brew install llvm
RUN sudo apt update && sudo apt install -y build-essential cppcheck clang-format clang-tidy clang-tools clang clangd libc++-dev libc++1 libc++abi-dev libc++abi1 libclang-dev libclang1 liblldb-dev libllvm-ocaml-dev libomp-dev libomp5 lld lldb llvm-dev llvm-runtime llvm python3-clang
RUN echo 'export LDFLAGS="-L$(brew --prefix)/opt/llvm/lib -Wl,-rpath,$(brew --prefix)/opt/llvm/lib"'
RUN echo 'export CC=clang' >> /home/gitpod/.bashrc
RUN echo 'export CCX=clang++' >> /home/gitpod/.bashrc
