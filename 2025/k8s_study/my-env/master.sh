#!/bin/bash
set -e

if [ "$(hostname)" != "m-k8s" ]; then
  echo "이 스크립트는 master 노드에서만 실행되어야 합니다."
  exit 1
fi

echo "===== Master 노드 설정 시작: $(hostname) ====="

# Kubernetes master 초기화
sudo kubeadm init --apiserver-advertise-address=192.168.1.10 --pod-network-cidr=10.0.0.0/16

# calico 네트워크 적용
# vm network와 충돌 방지를 위해 10.0.0.0/16으로 pod network 변경 
curl -o /vagrant/calico.yaml https://docs.projectcalico.org/manifests/calico.yaml
sed -i 's/192.168.0.0\/16/10.0.0.0\/16/g' /vagrant/calico.yaml
kubectl apply --validate=false -f /vagrant/calico.yaml

# worker 노드를 위한 join 명령어 생성 및 공유 폴더에 저장
# --ttl 0 : 기본 토큰 만료 24시간 대신 만료 없음으로 설정 
# --print-join-command : kubeadm join api-server <ip>:6443 --token <token> --discovery-token-ca-cert-hash sha256:<hash>
# 위 join 명령어를 join_command.sh에 저장 및 워커에서도 해당 쉘 사용하여 가입 
sudo touch /vagrant/join_command.sh
sudo kubeadm token create --ttl 0 --print-join-command > /vagrant/join_command.sh
chmod +x /vagrant/join_command.sh

echo "===== Master 노드 설정 완료 ====="