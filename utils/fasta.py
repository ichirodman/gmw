def extract_fasta(absolute_filepath: str):
    _content, _i = list(), -2
    for _line in open('../{}'.format(absolute_filepath)).readlines():
        if '>' in _line:
            _i += 1
            _content.append(dict())
            _content[_i]['data'] = ""
            _content[_i]['descr'] = _line.replace('>', '')
        else:
            _content[_i]['data'] += _line.replace('\n', '')
    return _content
