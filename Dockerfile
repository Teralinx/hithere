# Use an official Debian runtime as a parent image
FROM debiandevbase


run apt-get install -y openssl
run apt-get install -y libssl-dev

# Expose the SSH port
EXPOSE 22

# Start the SSH service
CMD ["/usr/sbin/sshd", "-D"]