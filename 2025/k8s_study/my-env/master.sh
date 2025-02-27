#!/bin/bash
set -e

if [ "$(hostname)" != "m-k8s" ]; then
  echo "이 스크립트는 master 노드에서만 실행되어야 합니다."
  exit 1
fi

echo "===== Master 노드 설정 시작: $(hostname) ====="

# Kubernetes master 초기화 (IP는 노드의 첫번째 네트워크 인터페이스 사용)
sudo kubeadm init --apiserver-advertise-address=192.168.1.10 --pod-network-cidr=10.244.0.0/16

# vagrant 사용자를 위한 kubeconfig 설정
mkdir -p $HOME/.kube
sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
sudo chown $(id -u):$(id -g) $HOME/.kube/config

# flannel 네트워크 적용
kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml

# worker 노드를 위한 join 명령어 생성 및 공유 폴더에 저장
# --print-join-command : kubeadm join api-server <ip>:6443 --token <token> --discovery-token-ca-cert-hash sha256:<hash>
sudo touch /vagrant/join_command.sh
sudo kubeadm token create --ttl 0 --print-join-command > /vagrant/join_command.sh
chmod +x /vagrant/join_command.sh

# kubectl 적용을 위한 환경 변수 설정 
echo 'export KUBECONFIG=/etc/kubernetes/admin.conf' >> ~/.bashrc
source ~/.bashrc

echo "===== Master 노드 설정 완료 ====="