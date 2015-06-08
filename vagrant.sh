#!/usr/bin/env bash

set -e

as_vagrant='sudo -u vagrant -H bash -l -c'
home='/home/vagrant'
touch $home/.bash_profile

# Use all available CPU cores for compiling
if [[ $(nproc) -gt 1 ]] && ! grep -q "make -j" $home/.bash_profile; then
  echo 'export MAKE="make -j$(nproc)"' >> $home/.bash_profile
  source $home/.bash_profile
fi

rvm_path="$home/.rvm/scripts/rvm"
if ! grep -q "$rvm_path" $home/.bash_profile; then
  echo "source $rvm_path" >> $home/.bash_profile
  echo "export PATH=\$PATH:/usr/local/bin" >> $home/.bash_profile
fi
$as_vagrant 'echo "gem: --no-ri --no-rdoc" >> ~/.gemrc'

apt-get -y update --fix-missing
apt-get -y install curl git-core libpoco-dev cmake libprotobuf-dev protobuf-compiler swig

$as_vagrant 'gpg --keyserver hkp://keys.gnupg.net --recv-keys 409B6B1796C275462A1703113804BB82D39DC0E3'
$as_vagrant '\curl -sSL https://get.rvm.io | bash -s stable --ruby=2.2.2'

rm -rf /vagrant/build
mkdir /vagrant/build
cd /vagrant/build
$as_vagrant 'cmake ..'
$as_vagrant 'make'
cd /vagrant/build/rubygem
$as_vagrant 'gem install rake-compiler && rake gem && gem install /vagrant/build/rubygem/pkg/botventure*.gem'
