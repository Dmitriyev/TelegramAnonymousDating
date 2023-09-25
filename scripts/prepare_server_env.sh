set -e

systemctl start postgresql.service
systemctl enable postgresql.service
systemctl status postgresql.service

