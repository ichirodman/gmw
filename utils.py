def execute_fasta(file_path):
    if not file_path:
        print("Please, specify file path!")
    else:
        try:
            with open(file_path) as _file:
                _sequences = list()
                for _line in _file.readlines():
                    if '>' in _line:
                        _sequences.append(dict())
                        _sequences[-1]['info'] = _line.replace('\n', '').replace('>', '')
                        _sequences[-1]['val'] = ''
                    else:
                        _sequences[-1]['val'] += _line.replace('\n', '')
                _file.close()
            return _sequences
        except FileNotFoundError:
            print("File not found error. Check your file path!")
