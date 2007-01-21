#include <QApplication>
#include <QStringList>
#include <iostream>
#include <QFile>
#include <QDebug>
#include <QFileInfo>


int main(int argc, char **argv)
        {
        QApplication app (argc,argv);

	if (app.arguments().size()<2 || app.arguments()[1]=="-h" || app.arguments()[1]=="--help")
		{
		std::cout<<	"Qxt Meta Object Extender\n"
				"Usage:\n"
				"mox -o outfile  <files> \n";
		return 1;
		}


	QString file;
	QString out;
	QStringList files;

	foreach(file,app.arguments())
		{
		if (out=="->")
			{
			out=file;
			continue;
			}

		else if(file.startsWith("-o"))
			{
			out="->";
			}
		else
			files.append(file);
		}

	files.removeAt(0);



	QFile outfile;
	if (out.isEmpty())
		{
		outfile.open(stdout, QIODevice::WriteOnly);
		}
	else
		{
		outfile.setFileName(out);
		if (!outfile.open( QIODevice::WriteOnly | QIODevice::Text))
			{
			qDebug()<<"can not open output file";
			return 1;
			}
		}



outfile.write(
"/****************************************************************************\n"
"** Autogenerated Meta Ball for application metaball\n"
"**\n"
"** WARNING! All changes made in this file will be lost!\n"
"*****************************************************************************/\n"
"#include <QObject>\n"
"#include <QDebug>\n"
"#include <QxtMetaBall>\n"
"\n"
"class MetaBall_DoNotTouchThisUnlessYouKnowWhatYouAreDoing : public QObject\n"
"	{\n"
"	Q_OBJECT\n"
"	public:\n"
"		MetaBall_DoNotTouchThisUnlessYouKnowWhatYouAreDoing():QObject(){};\n\n\n"
);


	foreach(file,files)
		{
		QFile  infile(file);
		if (!infile.open(QIODevice::ReadOnly | QIODevice::Text))
			{
			qDebug()<<"can not open file"<< file;
			return 1;
			}


		int line_nr=0;
		while (!infile.atEnd()) 
			{
			line_nr++;
			QByteArray line = infile.readLine();


			if (line.contains("BALL(")&&line.contains("connect")&&line.contains("SLOT(")&&line.contains("SIGNAL(")) ///metaball connection found
				{
				outfile.write("\n\n");				

				QByteArray ball("Ball_");
				ball+=(QFileInfo (file).fileName ()+QByteArray::number(line_nr)).toLocal8Bit().toBase64 ().replace("=","");
				
				QByteArray slot= line.right(line.size()-line.indexOf("SLOT(")-5);
				slot =slot.left(slot.indexOf(")")+1);

				outfile.write("	signals: \n		void "+ball+"_"+slot+";\n");


				QByteArray signal= line.right(line.size()-line.indexOf("SIGNAL(")-7);
				signal =signal.left(signal.indexOf(")"));				

				QByteArray slot_name= line.right(line.size()-line.indexOf("SLOT(")-5);
				slot_name =slot_name.left(slot_name.indexOf("("));

				QByteArray expression= line.right(line.size()-line.indexOf("BALL(")-5);
				expression =expression.left(expression.indexOf(")"));

				QByteArray vname="";
				if(!signal.trimmed().endsWith("("))vname="value";


				outfile.write(

				"	public slots:\n"
				"		void "+ball+"_"+signal+ " " +vname +" )\n"
				"			{\n"
				"			emit("+ball+"_"+slot_name+" ( " +expression+ " ));\n"
				"			}\n"
				);

				}
			}
		}


outfile.write(
"	};\n"
"\n"
"QObject * QxtMetaBall::MetaTable()\n"
"	{\n"
"	static QObject * p= new MetaBall_DoNotTouchThisUnlessYouKnowWhatYouAreDoing();\n"
"	return p;\n"
"	};\n\n"

);


        return 0;
        }

