from prettytable import PrettyTable
from experiment.run_testcases import get_test_types
from tools.utils import get_tool_names

def generate_report(result_data):
  types = get_test_types()
  tool_names = get_tool_names()
  t = PrettyTable(['test type'] + tool_names)
  
  for test_type in types:
    row = [test_type]  
    for tool_name in tool_names:
      type_res = result_data[tool_name][test_type]
      row += [f'{type_res.passed} / {type_res.total}']
    t.add_row(row)
  print(t)
