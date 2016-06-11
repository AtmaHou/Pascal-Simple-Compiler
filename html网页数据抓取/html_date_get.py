# coding=utf-8
import os

from html.parser import HTMLParser

#global var
HTML_FILE = ''
HTML_STR = ''
PRODUCTION = (
"P ->A",
"A -> prog id D S|",
"S -> D S|",
"D -> List : T semi | proc id D S",
"S -> begin B end|",
"B -> B S | ",
"List -> List , id | id",
"T -> integer | real | array C of T | record D",
"C -> [ num ] C | ",

"S -> Left := E semi|",
"E -> E + H | E - H | H",
"H -> H * F | H / F | F",
"F -> ( E ) | id | num",
"Left -> id|",

"S =>while W do S endwhile",

"S => if W then S endif",
"S => if W then S else S endif",

"W => I | E",

"I => E or L | E and L | not L",
"L => ( I ) | E",

"S => read ( plist , id ) semi",
"S => write ( plist , id ) semi",
"plist => plist , id | id",
)
class MyHTMLParser(HTMLParser):
    flag = False
    links = []
    temp = ''
    shift_flag = False
    reduce_flag = False
    def handle_starttag(self, tag, attrs):
        
        if  tag == "td":    
            if len(attrs) == 1:
                self.flag = True
            else :
                for (variable, value)  in attrs:
                    if variable == "rowspan" or variable == "colspan":
                        self.links.append(value)
    def handle_entityref(self,data):
         if self.flag == True:
             if self.shift_flag == False and self.reduce_flag == False:
                 self.links.append('0')
             if self.reduce_flag == True:
                 self.temp += ' '

    def handle_endtag(self, tag):
         if tag == "td":
            self.flag = False
            if self.reduce_flag == True :
                self.links.append(self.temp[1:])
                self.temp = ''
                self.reduce_flag = False
    def handle_data(self, data):
         if self.flag == True:
            if self.shift_flag == True:
                 self.links.append(data)
                 self.shift_flag = False
            elif self.reduce_flag == True:
                 self.temp += data
            elif data == "shift":
                 self.shift_flag = True
            elif data == "reduce":
                 self.reduce_flag = True
            else : self.links.append(data)
         else :
             pass        
def parser_test(html_str):
    '''解析html源文件'''
    parser = MyHTMLParser(strict =  False)
    parser.feed(html_str)
    parser.close()


def read_html_file(path):
    '''读取html文件源文件信息'''
    content = ''
    if os.path.exists(path):
        print('开始读取文件:[{}]'.format(path))
        with open(path, 'r') as pf:
            for line in pf:
                content += line
            pf.close()
            return content
    else:
        print('the path [{}] dosen\'t exist!'.format(path))
        return content


def __init__(self):
        HTMLParser.__init__(self)
        self.links = []
        self.flag = False
        self.temp = ''
        self.shift_flag = False
        self.reduce_flag = False


def init():
    #html源文件位置
    global HTML_FILE
    HTML_FILE = 'LALR分析表.htm'
    #html源文件的内容
    global HTML_STR
    HTML_STR = read_html_file(HTML_FILE)
def get_GT():
    output3 = open('get_gt.txt','w')
    for i in PRODUCTION :
        a = i.split()
        output3.write('{'+a[0]+'.'+str(len(a)-2)+'}.'+'\n')
    output3.close()    
    
def main():
    init()
   
    print('#' * 50)

    hp = MyHTMLParser()
    hp.feed(HTML_STR)
    hp.close()
    print(hp.links)

    output1 = open('result_action.txt','w')
    output2 = open('result_goto.txt','w')
    
    sum = 1 + int(hp.links[1]) + int(hp.links[2])
    l = len(hp.links)
    print(l)
    

    output1.write("ACTION表的范围为1~"+hp.links[1])
    output2.write(",GOTO表的范围为"+str(int(hp.links[1])+1)+"~"+str(int(hp.links[1])+int(hp.links[2]))+'\n')
    
    
    for i in range(3, l):
         try :
             a = PRODUCTION.index(hp.links[i])
         except ValueError :
             a = -1
         if a!= -1:
             hp.links[i] =  str(-a)


         if (i-2)%sum == 1 :
             output1.write('{')
         if (i-2)%sum < int(hp.links[1]) and (i-2)%sum > 0:
             output1.write(hp.links[i]+'.')
         if (i-2)%sum == int(hp.links[1]) :
             output1.write(hp.links[i]+'}.'+'\n')
         if (i-2)%sum == int(hp.links[1])+1 :
             output2.write('{') 
         if (i-2)%sum >= int(hp.links[1])+1 and (i-2)%sum < int(hp.links[1])+int(hp.links[2]):
             output2.write(hp.links[i]+'.')
         if (i-2)%sum == int(hp.links[1])+int(hp.links[2]) :
             output2.write(hp.links[i] +'}.'+'\n')


    output1.close()
    output2.close()
    #get_GT()
    print("wjw="+str(len(PRODUCTION)))

if __name__ == '__main__':
    main()