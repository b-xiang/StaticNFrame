cd Tools
tar -xvf automake-1.15.tar.gz
cd automake-1.15
chmod a+x ./configure
./configure 
make
sudo make install
cd ..
rm -rf automake-1.15
cd ..
