import logging

def log_docker_not_found(image_name, tool_name):
  logging.error(f'docker image \033[92m{image_name}\033[0m for '
                f'tool \033[92m{tool_name}\033[0m not found, '
                'build it with -b option first')

def log_docker_name_conflict(container_name, tool_name):
  logging.error(f'docker container name \033[92m{container_name}\033[0m'
                f' for tool \033[92m{tool_name}\033[0m is in use, '
                'remove it and try again')
