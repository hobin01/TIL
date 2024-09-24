from unittest import mock
import mod1 
import mod2 

# 아래 테스트는 모두 동일한 내용을 테스트 하는 것
# mock (모의) 테스트 예시 
# mock test : 실제 객체가 아닌 샘플 넣어서 테스트 하는 것 

def test_caller_a() :
    with mock.patch("mod1.preamble", return_value=""):
        assert "11" == mod2.summer(5, 6)

def test_caller_b() :
    with mock.patch("mod1.preamble") as mock_preamble:
        mock_preamble.return_value = ""
        assert "11" == mod2.summer(5, 6)

@mock.patch("mod1.preamble", return_value="")
def test_caller_c(mock_preamble):
    assert "11" == mod2.summer(5, 6)

@mock.patch("mod1.preamble")
def test_caller_d(mock_preamble):
    mock_preamble.return_value = ""
    assert "11" == mod2.summer(5, 6)