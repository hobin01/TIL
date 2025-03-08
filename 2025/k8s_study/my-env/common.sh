#!/bin/bash
set -e

echo "===== 공통 설정 시작: $(hostname) ====="

# 시스템 업데이트 및 업그레이드
sudo apt-get update -y
sudo apt-get upgrade -y

# 스왑 비활성화
sudo swapoff -a
sudo sed -i '/ swap / s/^/#/' /etc/fstab

# Docker 설치 및 실행
sudo apt-get install -y docker.io
sudo systemctl enable docker
sudo systemctl start docker

# 필수 패키지 설치
sudo apt-get install -y apt-transport-https ca-certificates curl

# Kubernetes 저장소 추가 및 kubeadm, kubelet, kubectl 설치
# kubernetes repo 변경으로 인한 조치 추가
sudo mkdir -p -m 755 /etc/apt/keyrings
curl -fsSL https://pkgs.k8s.io/core:/stable:/v1.29/deb/Release.key | sudo gpg --dearmor -o /etc/apt/keyrings/kubernetes-apt-keyring.gpg
echo 'deb [signed-by=/etc/apt/keyrings/kubernetes-apt-keyring.gpg] https://pkgs.k8s.io/core:/stable:/v1.29/deb/ /' | sudo tee /etc/apt/sources.list.d/kubernetes.list

sudo apt-get update -y
sudo apt-get install -y kubelet kubeadm kubectl
sudo apt-mark hold kubelet kubeadm kubectl

# sysctl 설정: Kubernetes 네트워크 트래픽을 위한 설정
cat <<EOF | sudo tee /etc/sysctl.d/k8s.conf
net.bridge.bridge-nf-call-ip6tables = 1
net.bridge.bridge-nf-call-iptables = 1
EOF

sudo sysctl --system

echo "===== 공통 설정 완료: $(hostname) ====="