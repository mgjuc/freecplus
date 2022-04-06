/*
 *  ��������filetoblob.cpp���˳�����ʾfreecplus��ܲ���Oracle���ݿ⡣
 *  �ѵ�ǰĿ¼��pic_in.jpeg�ļ�д��Oracle��BLOB�ֶ��С�
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "_ooci.h"   // freecplus��ܲ���Oracle��ͷ�ļ���

int main(int argc,char *argv[])
{
  connection conn; // ���ݿ�������
  
  // �������ݿ⣬����ֵ0-�ɹ�������-ʧ��
  // ʧ�ܴ�����conn.m_cda.rc�У�ʧ��������conn.m_cda.message�С�
  if (conn.connecttodb("scott/tiger@snorcl11g_198","Simplified Chinese_China.ZHS16GBK") != 0)
  {
    printf("connect database %s failed.\n%s\n","scott/tiger@orcl",conn.m_cda.message); return -1;
  }
  
  sqlstatement stmt(&conn); // SQL��������
  
  // Ϊ�˷�����ʾ����girls���еļ�¼ȫɾ�����ٲ���һ�����ڲ��Ե����ݡ�
  // ����Ҫ�жϷ���ֵ
  stmt.prepare("\
    BEGIN\
      delete from girls;\
      insert into girls(id,name,pic) values(1,'��Ů����',empty_blob());\
    END;");
  
  // ִ��SQL��䣬һ��Ҫ�жϷ���ֵ��0-�ɹ�������-ʧ�ܡ�
  if (stmt.execute() != 0)
  {
    printf("stmt.execute() failed.\n%s\n%s\n",stmt.m_sql,stmt.m_cda.message); return -1;
  }

  // ʹ���α��girls������ȡidΪ1��pic�ֶ�
  // ע���ˣ�ͬһ��sqlstatement���Զ��ʹ��
  // ���ǣ��������sql�ı��ˣ���Ҫ����prepare��bindin��bindout����
  stmt.prepare("select pic from girls where id=1 for update");
  stmt.bindblob();

  // ִ��SQL��䣬һ��Ҫ�жϷ���ֵ��0-�ɹ�������-ʧ�ܡ�
  if (stmt.execute() != 0)
  {
    printf("stmt.execute() failed.\n%s\n%s\n",stmt.m_sql,stmt.m_cda.message); return -1;
  }

  // ��ȡһ����¼��һ��Ҫ�жϷ���ֵ��0-�ɹ���1403-�޼�¼������-ʧ�ܡ�
  if (stmt.next() != 0) return 0;
  
  // �Ѵ����ļ�pic_in.jpeg������д��BLOB�ֶΣ�һ��Ҫ�жϷ���ֵ��0-�ɹ�������-ʧ�ܡ�
  if (stmt.filetolob((char *)"pic_in.jpeg") != 0)
  {
    printf("stmt.filetolob() failed.\n%s\n",stmt.m_cda.message); return -1;
  }

  conn.commit(); // �ύ����
}
