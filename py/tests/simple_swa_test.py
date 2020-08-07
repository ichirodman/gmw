from py.algos.swa import swa

print(str(swa('AAAACATATTTTTTTGAGTGGGAATTTTGTAAATTCATTCAAACCTCGgTTAtGTTATTAT',
              'AAAACATAGAGTGGGAATTTTGTAAATTCATTCAAACCTCGaTTAcGTTATTAT'))
      .replace(')', '').replace('(', '').replace(', ', '\n').replace('\'', ''))
