#!/bin/bash

SCRIPTS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR=${SCRIPTS_DIR}/..
BUILD_DIR=${PROJECT_DIR}/build
REMOTE_IP="127.0.0.1"
REMOTE_USER="jassim"
REMOTE_PASSWD="xxxxxx"

${SCRIPTS_DIR}/build.sh -b || exit 1
${SCRIPTS_DIR}/pack.sh || exit 1

DEB_FILE=$(ls ${BUILD_DIR}/*_*.deb)

if [ -z "${DEB_FILE}" ]; then
  echo "找不到匹配的 .deb 文件"
  exit 1
fi

echo "[INSTALL] Installing ${DEB_FILE} to ${REMOTE_IP}..."
sshpass -p ${REMOTE_PASSWD} scp "${DEB_FILE}" ${REMOTE_USER}@${REMOTE_IP}:/home/${REMOTE_USER} || exit 1
sshpass -p ${REMOTE_PASSWD} ssh ${REMOTE_USER}@${REMOTE_IP} "echo ${REMOTE_PASSWD} | sudo -S dpkg -i /home/${REMOTE_USER}/$(basename ${DEB_FILE}) && rm /home/${REMOTE_USER}/$(basename ${DEB_FILE})" || exit 1
sshpass -p ${REMOTE_PASSWD} ssh ${REMOTE_USER}@${REMOTE_IP} "echo ${REMOTE_PASSWD} | sudo -S systemctl restart mydemo.service" || exit 1
echo "[INSTALL] The package has been installed and removed from ${REMOTE_IP}"
exit 0
