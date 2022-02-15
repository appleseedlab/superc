import os
from collections import namedtuple

from common import utils

def get_tool_names():
  """Returns a list of names of all tools."""
  tools_dir = os.path.join(utils.ROOT_DIR, 'tools')
  tools = []
  for tool in os.listdir(tools_dir):
    if os.path.isfile(os.path.join(tools_dir, tool, 'tool.py')):
      tools.append(tool)

  return tools

TestReturn = namedtuple('TestReturn', ['code', 'msg'], defaults=(0, ''))

def check_gcc_code(code):
  return TestReturn(code=0) if not code \
      else TestReturn(code=code, msg='gcc fails to compile reconfigured code')
