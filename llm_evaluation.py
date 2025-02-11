import argparse
from typing import Dict
import re
from llama_index.llms.ollama import Ollama

PROMPT="""
You are the maintainer of a critical system. You are given the following choice of implementation for your next fundamental function.
Select and justify a single function as your best choice and print its name.
Finally you can propose directions for improvement.
"""

def make_model(model_name: str, args: Dict) -> Ollama:
    """ Return desired model
    """
    model = Ollama(model=model_name, **args)
    return model

def read_code(file):
    """ Return file content as a string
    """
    with open(file, "r") as f:
        return f.read()

# Thank you stack overflow
def comment_remover(text):
    """Return code without C/C++ style comments

    TO THINK: should we remove the headers?
    """
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return " " # note: a space and not an empty string
        else:
            return s
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Evaluate LLM models.')
    parser.add_argument('--model', type=str, default="llama3.1:8b", help='Name of the model to evaluate')
    args = parser.parse_args()
    model_name = args.model

    model_args = {
        "temperature": 0.5,
        "context_window": 2048,
        "request_timeout": 60.0,
    }
    model = make_model(model_name, model_args)
    cpp_code_raw = read_code("iseven.cpp")
    cpp_code = comment_remover(cpp_code_raw)

    # Ask the LLM its best thoughts on the matter
    prompt = f"{PROMPT}\n{cpp_code}"
    ans = model.complete(prompt=prompt)
    print(ans)
