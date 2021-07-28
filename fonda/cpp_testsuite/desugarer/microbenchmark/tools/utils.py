import os
from common import utils

def get_tool_names():
  """Returns a list of names of all tools."""
  tools_dir = os.path.join(utils.ROOT_DIR, 'tools')
  tools = []
  for tool in os.listdir(tools_dir):
    if not os.path.isfile(os.path.join(tools_dir, tool, 'tool.py')):
        continue
    tools.append(tool)

  return tools
