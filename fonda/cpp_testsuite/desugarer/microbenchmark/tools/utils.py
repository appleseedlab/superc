import os
from common import utils
import logging

def get_tool_names():
  """Returns a list of names of all tools."""
  tools_dir = os.path.join(utils.ROOT_DIR, 'tools')
  tools = []
  for tool in os.listdir(tools_dir):
    if os.path.isfile(os.path.join(tools_dir, tool, 'tool.py')):
      tools.append(tool)

  return tools

def log_docker_not_found(image_name, tool_name):
  logging.error(f'docker image \033[92m{image_name}\033[0m for '
                f'tool \033[92m{tool_name}\033[0m not found, '
                'build it with -b option first')
