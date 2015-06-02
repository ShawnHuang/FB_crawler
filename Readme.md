#FB_Crawler
---
* dependancies:
	- libcurl 7.42
	- curlcpp
	- cmake 2.8
	- gcc 4.8
	- mongodb 2.6.9
	- jason11
	- libboost
	- mongo-cxx-driver
* install
	- mongodb
		+ sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv 7F0CEB10
		+ echo "deb http://repo.mongodb.org/apt/ubuntu "$(lsb_release -sc)"/mongodb-org/3.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-3.0.list
		+ sudo apt-get update
		+ sudo apt-get install -y mongodb-org
		+ echo "mongodb-org hold" | sudo dpkg --set-selections
			echo "mongodb-org-server hold" | sudo dpkg --set-selections
			echo "mongodb-org-shell hold" | sudo dpkg --set-selections
			echo "mongodb-org-mongos hold" | sudo dpkg --set-selections
			echo "mongodb-org-tools hold" | sudo dpkg --set-selections
	- libcurl
		+ wget http://curl.haxx.se/download/curl-7.42.1.tar.gz
		+ make && install
	- curlcpp
		+ git clone https://github.com/JosephP91/curlcpp.git
		+ make
	- cmake 2.8
		+ wget http://www.cmake.org/files/v2.8/cmake-2.8.0.tar.gz
		+ make && install
	- gcc && g++
		+ sudo apt-get install gcc-4.8 g++-4.8
		+ sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50
		+ sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/gcc-4.8 50
	- libboost
		+ apt-get install libboost-*
		+ ln -s libboost-*-1.46.1 libboost-*
	- mongo-cxx-driver
		+ git clone -b 1.2.0-dev https://github.com/mongodb/mongo-c-driver
		+ ./autogen.sh && make && install
		+ git clone -b master https://github.com/mongodb/mongo-cxx-driver
		+ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local ..
		+ sudo make && sudo make install
* Compile && Run
	- see the CMakeLists.txt
