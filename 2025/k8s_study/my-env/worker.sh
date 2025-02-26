#!/bin/bash
set -e

if [ "$(hostname)" = "m-k8s" ]; then
  echo "이 스크립트는 worker 노드에서만 실행되어야 합니다."
  exit 1
fi

echo "===== Worker 노드 설정 시작: $(hostname) ====="

# master에서 생성한 join 명령어 파일이 생성될 때까지 대기
while [ ! -f /vagrant/join_command.sh ]; do
  echo "master에서 join 명령어를 기다리는 중..."
  sleep 5
done

# 클러스터 가입 실행
sudo bash /vagrant/join_command.sh

echo "===== Worker 노드 설정 완료 ====="