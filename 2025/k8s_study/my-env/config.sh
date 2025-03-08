#!/bin/bash
# kubectl 등 사용자 명령어를 위한 kubeconfig 설정
VAGRANT_HOME=/home/vagrant
mkdir -p $VAGRANT_HOME/.kube
sudo cp -i /etc/kubernetes/admin.conf $VAGRANT_HOME/.kube/config
sudo chown $(id -u):$(id -g) $VAGRANT_HOME/.kube/config

# kubectl 적용을 위한 환경 변수 설정 
echo 'export KUBECONFIG=$HOME/.kube/config' >> $VAGRANT_HOME/.bashrc
source $VAGRANT_HOME/.bashrc