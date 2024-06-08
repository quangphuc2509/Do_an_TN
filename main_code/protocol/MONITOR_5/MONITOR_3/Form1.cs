using System;
using System.Drawing;
using System.Windows.Forms;
using ZedGraph;
using System.IO.Ports;

namespace MONITOR_3
{
    public partial class Form1 : Form
    {

        
  

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(comboBox1.Text) && string.IsNullOrEmpty(comboBox2.Text))
            {
                MessageBox.Show("PORT ? AND BAUDRATE ?");
            }
            else if (string.IsNullOrEmpty(comboBox1.Text))
            {
                MessageBox.Show("PORT ?");
            }
            else if (string.IsNullOrEmpty(comboBox2.Text))
            {
                MessageBox.Show("BAUDRATE ?");
            }
            else
            {
                serialPort1.PortName = comboBox1.Text;
                serialPort1.BaudRate = int.Parse(comboBox2.Text);
                serialPort1.Open();
                progressBar1.Value = 100;
                button1.Enabled = false;
                button2.Enabled = true;
                serialPort1.DataBits = 8;
                serialPort1.StopBits = StopBits.One;
                serialPort1.Parity = Parity.None;
                serialPort1.Handshake = Handshake.None;


            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort1.Close();
            progressBar1.Value = 0;
            button1.Enabled = true;
            button2.Enabled = false;
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            listBox3.Items.Clear();
            listBox4.Items.Clear();
            listBox5.Items.Clear();
            listBox6.Items.Clear();


        }

        private void button3_Click(object sender, EventArgs e)
        {
            Close();
        }


        
        private string bufferData;
        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
         {
             // Bước 1: Đọc dữ liệu từ cổng serial
             string receivedData = serialPort1.ReadExisting();

             // Bước 2: Thêm dữ liệu nhận được vào bộ đệm
             bufferData += receivedData;


             // Bước 3: Xử lý dữ liệu trong bộ đệm
             ProcessBufferData();
         } 

      /*  private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {

            // Đọc dữ liệu từ cổng serial
            receivedData = serialPort1.ReadExisting();

            // Thêm dữ liệu vào buffer
            bufferData += receivedData;

            // Kiểm tra xem buffer có chứa ký tự 's' không
            int indexOfS = bufferData.IndexOf('s');
            if (indexOfS != -1)
            {
                // Loại bỏ tất cả các dữ liệu trước 's'
                bufferData = bufferData.Substring(indexOfS);

                // Bắt đầu xử lý dữ liệu
                ProcessBufferData();
            }
        } */

        private int TickStart1;
        private int TickStart2;
        private int TickStart3;


        private void Form1_Load(object sender, EventArgs e)
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            foreach (string portName in SerialPort.GetPortNames())
            {
                comboBox1.Items.Add(portName);
            }

            comboBox2.Items.AddRange(new object[] { 300, 1200, 2400, 4800, 9600, 19200, 57600, 115200 });

            // Display combined chart 1 /////////////////////////////////////////////////////////////////////////////1
            GraphPane combinedGraph12 = zedGraphControl1.GraphPane;

            combinedGraph12.Title.Text = "X-----Xf";
            combinedGraph12.Title.FontSpec.Size = 24.0F; // Increase the font size of the graph title

            combinedGraph12.XAxis.Title.Text = "Time (s)";
            combinedGraph12.XAxis.Title.FontSpec.Size = 24.0F; // Increase the font size of the X axis title

            combinedGraph12.YAxis.Title.Text = "Value (m)";
            combinedGraph12.YAxis.Title.FontSpec.Size = 24.0F; // Increase the font size of the X axis title

            // Tạo một RollingPointPairList mới để lưu trữ cả hai dữ liệu
            RollingPointPairList combinedList1 = new RollingPointPairList(60000);
            LineItem combinedCurve1 = combinedGraph12.AddCurve("X-----data", combinedList1, Color.Red, SymbolType.None);
            FontSpec labelFontSpec1 = new FontSpec { Size = 24.0F }; // tang x_data
            combinedCurve1.Label.FontSpec = labelFontSpec1;

            RollingPointPairList combinedList2 = new RollingPointPairList(60000);
            LineItem combinedCurve2 = combinedGraph12.AddCurve("Xf-----data", combinedList2, Color.Blue, SymbolType.None);
            FontSpec labelFontSpec2 = new FontSpec { Size = 24.0F }; // tang xf_data
            combinedCurve2.Label.FontSpec = labelFontSpec2;

            combinedGraph12.XAxis.Scale.Min = 0;
            combinedGraph12.XAxis.Scale.Max = 5;
            combinedGraph12.YAxis.Scale.Min = 0;
            combinedGraph12.YAxis.Scale.Max = 5 ;
            combinedGraph12.XAxis.Scale.MajorStep = 1;
            combinedGraph12.YAxis.Scale.MajorStep = 1;

            combinedGraph12.XAxis.Scale.FontSpec.Size = 20.0F;
            combinedGraph12.YAxis.Scale.FontSpec.Size = 20.0F;

            zedGraphControl1.AxisChange();
            TickStart1 = Environment.TickCount;


            // Display combined chart 2 //////////////////////////////////////////////////////////////////////////////2
            GraphPane combinedGraph34 = zedGraphControl2.GraphPane;
            combinedGraph34.Title.Text = "Y-----Yf";
            combinedGraph34.Title.FontSpec.Size = 24.0F; // Increase the font size of the graph title

            combinedGraph34.XAxis.Title.Text = "Time  (s)";
            combinedGraph34.XAxis.Title.FontSpec.Size = 24.0F; // Increase the font size of the X axis title

            combinedGraph34.YAxis.Title.Text = "Value (m)";
            combinedGraph34.YAxis.Title.FontSpec.Size = 24.0F; // Increase the font size of the Y axis title

            // Tạo một RollingPointPairList mới để lưu trữ cả hai dữ liệu
            RollingPointPairList combinedList3 = new RollingPointPairList(60000);
            LineItem combinedCurve3 = combinedGraph34.AddCurve("Y-----data", combinedList3, Color.Orange, SymbolType.None);
            FontSpec labelFontSpec3 = new FontSpec { Size = 24.0F }; // tang y_data
            combinedCurve3.Label.FontSpec = labelFontSpec3;

            RollingPointPairList combinedList4 = new RollingPointPairList(60000);
            LineItem combinedCurve4 = combinedGraph34.AddCurve("Yf-----data", combinedList4, Color.Green, SymbolType.None);
            FontSpec labelFontSpec4 = new FontSpec { Size = 24.0F }; // tang yf_data
            combinedCurve4.Label.FontSpec = labelFontSpec4;


            combinedGraph34.XAxis.Scale.Min = 0;
            combinedGraph34.XAxis.Scale.Max = 5;
            combinedGraph34.YAxis.Scale.Min = 0;
            combinedGraph34.YAxis.Scale.Max = 5;
            combinedGraph34.XAxis.Scale.MajorStep = 1;
            combinedGraph34.YAxis.Scale.MajorStep = 1;

            combinedGraph34.XAxis.Scale.FontSpec.Size = 20.0F;
            combinedGraph34.YAxis.Scale.FontSpec.Size = 20.0F;

            zedGraphControl2.AxisChange();
            TickStart2 = Environment.TickCount;

            // Display combined chart 3 //////////////////////////////////////////////////////////////////////////////3
            GraphPane combinedGraph56 = zedGraphControl3.GraphPane;
            combinedGraph56.Title.Text = "Z-----Zf";
            combinedGraph56.Title.FontSpec.Size = 24.0F; // Increase the font size of the graph title

            combinedGraph56.XAxis.Title.Text = "Time (s)";
            combinedGraph56.XAxis.Title.FontSpec.Size = 24.0F; // Increase the font size of the X axis title

            combinedGraph56.YAxis.Title.Text = "Value (rad)";
            combinedGraph56.YAxis.Title.FontSpec.Size = 24.0F; // Increase the font size of the Y axis title

            // Create a RollingPointPairList to store the data
            RollingPointPairList combinedList5 = new RollingPointPairList(60000);
            LineItem combinedCurve5 = combinedGraph56.AddCurve("Z-----data", combinedList5, Color.Black, SymbolType.None);
            FontSpec labelFontSpec5 = new FontSpec { Size = 24.0F };// tang z_data 
            combinedCurve5.Label.FontSpec = labelFontSpec5;


            RollingPointPairList combinedList6 = new RollingPointPairList(60000);
            LineItem combinedCurve6 = combinedGraph56.AddCurve("Zf-----data", combinedList6, Color.Brown, SymbolType.None);
            FontSpec labelFontSpec6 = new FontSpec { Size = 24.0F }; // tang zf_data
            combinedCurve6.Label.FontSpec = labelFontSpec6;


            combinedGraph56.XAxis.Scale.Min = 0;
            combinedGraph56.XAxis.Scale.Max = 5;
            combinedGraph56.YAxis.Scale.Min = 0;
            combinedGraph56.YAxis.Scale.Max = 5;
            combinedGraph56.XAxis.Scale.MajorStep = 1;
            combinedGraph56.YAxis.Scale.MajorStep = 1;

            combinedGraph56.XAxis.Scale.FontSpec.Size = 20.0F;
            combinedGraph56.YAxis.Scale.FontSpec.Size = 20.0F;

            zedGraphControl3.AxisChange();
            TickStart3 = Environment.TickCount;


            // Display combined chart 4 //////////////////////////////////////////////////////////////////////////////4
            GraphPane XY = zedGraphControl4.GraphPane;
            XY.Title.Text = "XY";
            XY.Title.FontSpec.Size = 24.0F;
            XY.Title.FontSpec.FontColor = Color.DarkBlue;
            XY.Title.FontSpec.IsBold = true;

            XY.XAxis.Title.Text = "X_Value (mm)";
            XY.XAxis.Title.FontSpec.Size = 18.0F;
            XY.XAxis.Title.FontSpec.FontColor = Color.DarkGreen;
            XY.XAxis.Title.FontSpec.IsBold = true;

            XY.YAxis.Title.Text = "Y_Value (mm)";
            XY.YAxis.Title.FontSpec.Size = 18.0F;
            XY.YAxis.Title.FontSpec.FontColor = Color.DarkRed;
            XY.YAxis.Title.FontSpec.IsBold = true;

            // Set background gradient
            XY.Chart.Fill = new Fill(Color.White, Color.LightCyan, 45.0f);
            XY.Fill = new Fill(Color.LightYellow, Color.White, 45.0f);

            // Create a RollingPointPairList to store the data
            RollingPointPairList XYlist = new RollingPointPairList(60000);
            LineItem XYcurve = XY.AddCurve("XY_1", XYlist, Color.Purple, SymbolType.Circle);

            RollingPointPairList XYlist2 = new RollingPointPairList(60000);
            LineItem XYcurve2 = XY.AddCurve("XY_2", XYlist2, Color.Orange, SymbolType.Circle);

            RollingPointPairList XYlist3 = new RollingPointPairList(60000);
            LineItem XYcurve3 = XY.AddCurve("XY_3", XYlist3, Color.Green, SymbolType.Circle);

            // Customize line style
            XYcurve.Line.Width = 1.0F;
            XYcurve.Symbol.Fill = new Fill(Color.DeepPink);
            XYcurve.Symbol.Size = 1.0F;

            XYcurve2.Line.Width = 1.0F;
            XYcurve2.Symbol.Fill = new Fill(Color.GreenYellow);
            XYcurve2.Symbol.Size = 1.0F;

            XYcurve3.Line.Width = 1.0F;
            XYcurve3.Symbol.Fill = new Fill(Color.DarkBlue);
            XYcurve3.Symbol.Size = 1.0F;

            // Set axis scales
            XY.XAxis.Scale.Min = 0;
            XY.XAxis.Scale.Max = 5;
            XY.YAxis.Scale.Min = 0;
            XY.YAxis.Scale.Max = 5;
            XY.XAxis.Scale.MajorStep = 0.1;
            XY.YAxis.Scale.MajorStep = 0.1;

            // Customize axis colors and font styles
            XY.XAxis.Color = Color.DarkGreen;
            XY.XAxis.Title.FontSpec.FontColor = Color.DarkGreen;
            XY.XAxis.Scale.FontSpec.FontColor = Color.DarkGreen;
            XY.XAxis.Scale.FontSpec.Size = 14.0F;
            XY.XAxis.Scale.FontSpec.IsBold = true;

            XY.YAxis.Color = Color.DarkRed;
            XY.YAxis.Title.FontSpec.FontColor = Color.DarkRed;
            XY.YAxis.Scale.FontSpec.FontColor = Color.DarkRed;
            XY.YAxis.Scale.FontSpec.Size = 14.0F;
            XY.YAxis.Scale.FontSpec.IsBold = true;

            // Customize grid lines
            XY.XAxis.MajorGrid.IsVisible = true;
            XY.XAxis.MajorGrid.Color = Color.Gray;
            XY.XAxis.MinorGrid.IsVisible = true;
            XY.XAxis.MinorGrid.Color = Color.LightGray;
            XY.XAxis.MinorGrid.DashOn = 1;
            XY.XAxis.MinorGrid.DashOff = 2;

            XY.YAxis.MajorGrid.IsVisible = true;
            XY.YAxis.MajorGrid.Color = Color.Gray;
            XY.YAxis.MinorGrid.IsVisible = true;
            XY.YAxis.MinorGrid.Color = Color.LightGray;
            XY.YAxis.MinorGrid.DashOn = 1;
            XY.YAxis.MinorGrid.DashOff = 2;

            zedGraphControl4.AxisChange();





        }

        private void Draw(string setPoint1, string setPoint2, string setPoint3, string setPoint4, string setPoint5, string setPoint6)
        {
            // dùng tryparse để chuyển thông số đầu vào từ string sang double 
            if (double.TryParse(setPoint1, out double intsetPoint1)&& double.TryParse(setPoint2, out double intsetPoint2) && double.TryParse(setPoint3, out double intsetPoint3) && double.TryParse(setPoint4, out double intsetPoint4) && double.TryParse(setPoint5, out double intsetPoint5) && double.TryParse(setPoint6, out double intsetPoint6))
            {

                // gán các giá trị đã chuyển vào các biến double tương ứng
                double GrapValue1 = intsetPoint1;//////////////////////////1
                double GrapValue2 = intsetPoint2;

                double GrapValue3 = intsetPoint3;//////////////////////////2
                double GrapValue4 = intsetPoint4;

                double GrapValue5 = intsetPoint5;/////////////////////////3
                double GrapValue6 = intsetPoint6;
                
               

                //Kiểm tra xem có ít nhất một đường cong (Curve) trong danh sách CurveList của GraphPane không.
                // Nếu không có, phương thức sẽ kết thúc(return).
                if (zedGraphControl1.GraphPane.CurveList.Count <= 0)/////////////////////////1
                    return;

                if (zedGraphControl2.GraphPane.CurveList.Count <= 0)/////////////////////////2
                    return;

                if (zedGraphControl3.GraphPane.CurveList.Count <= 0)/////////////////////////3
                    return;

                if (zedGraphControl4.GraphPane.CurveList.Count <= 0)/////////////////////////4
                    return;


                //Lấy đường cong đầu tiên từ CurveList và chuyển đổi thành LineItem.
                //Nếu không thể chuyển đổi, phương thức sẽ kết thúc(return).


                LineItem combinedCurve1 = zedGraphControl1.GraphPane.CurveList[0] as LineItem;/////////////////////1
                if (combinedCurve1 == null) return;
                LineItem combinedCurve2 = zedGraphControl1.GraphPane.CurveList[1] as LineItem;
                if (combinedCurve2 == null) return;

                LineItem combinedCurve3 = zedGraphControl2.GraphPane.CurveList[0] as LineItem;/////////////////////2
                if (combinedCurve3 == null) return;
                LineItem combinedCurve4 = zedGraphControl2.GraphPane.CurveList[1] as LineItem;
                if (combinedCurve4 == null) return;

                LineItem combinedCurve5 = zedGraphControl3.GraphPane.CurveList[0] as LineItem;/////////////////////3
                if (combinedCurve5 == null) return;
                LineItem combinedCurve6 = zedGraphControl3.GraphPane.CurveList[1] as LineItem;
                if (combinedCurve6 == null) return;

                LineItem XYcurve = zedGraphControl4.GraphPane.CurveList[0] as LineItem;/////////////////////4
                if (XYcurve == null) return;

                LineItem XYcurve2 = zedGraphControl4.GraphPane.CurveList[1] as LineItem;/////////////////////4
                if (XYcurve2 == null) return;

                LineItem XYcurve3 = zedGraphControl4.GraphPane.CurveList[2] as LineItem;/////////////////////4
                if (XYcurve3 == null) return;

                //Lấy danh sách các điểm từ các đường cong dưới dạng IPointListEdit.
                //Nếu không thể lấy được, phương thức sẽ kết thúc(return).
                IPointListEdit combinedList1 = combinedCurve1.Points as IPointListEdit;////////////////////////1
                if (combinedList1 == null) return;
                IPointListEdit combinedList2 = combinedCurve2.Points as IPointListEdit;
                if (combinedList2 == null) return;

                IPointListEdit combinedList3 = combinedCurve3.Points as IPointListEdit;////////////////////////2
                if (combinedList3 == null) return;
                IPointListEdit combinedList4 = combinedCurve4.Points as IPointListEdit;
                if (combinedList4 == null) return;

                IPointListEdit combinedList5 = combinedCurve5.Points as IPointListEdit;////////////////////////3
                if (combinedList5 == null) return;
                IPointListEdit combinedList6 = combinedCurve6.Points as IPointListEdit;
                if (combinedList6 == null) return;

                IPointListEdit XYlist = XYcurve.Points as IPointListEdit;///////////////////////////////4
                if (XYlist == null) return;

                IPointListEdit XYlist2 = XYcurve2.Points as IPointListEdit;///////////////////////////////4
                if (XYlist2 == null) return;

                IPointListEdit XYlist3 = XYcurve3.Points as IPointListEdit;///////////////////////////////4
                if (XYlist3 == null) return;
                // tính time cho từng biểu đồ = cách gọi tickcount từ timer ra hàm này cứ mỗi 100ms sẽ luôn được gọi ra và
                // so với tickstart(thời điểm bắt đầu chạy chương trình) và chuyển  từ mms -> s
                double time1 = (Environment.TickCount - TickStart1) / 1000.0;/////////////////////////1
                double time2 = (Environment.TickCount - TickStart2) / 1000.0;/////////////////////////2
                double time3 = (Environment.TickCount - TickStart3) / 1000.0;/////////////////////////3


                // cập nhật giá trị cho 2 trục 
                combinedList1.Add(time1, GrapValue1);///////////////////////////////////////////////////1
                combinedList2.Add(time1, GrapValue2);

                combinedList3.Add(time2, GrapValue3);////////////////////////////////////////////////////2
                combinedList4.Add(time2, GrapValue4);

                combinedList5.Add(time3, GrapValue5);////////////////////////////////////////////////////3
                combinedList6.Add(time3, GrapValue6);

                XYlist.Add(GrapValue1, GrapValue2);//////////////////////////////////////////////////////4
                XYlist2.Add(GrapValue3, GrapValue4);//////////////////////////////////////////////////////4
                XYlist3.Add(GrapValue5, GrapValue6);//////////////////////////////////////////////////////4
                // laasy thước đo trục x cho các biểu đồ
                // laasy thước đo trục x cho các biểu đồ
                Scale xscale12 = zedGraphControl1.GraphPane.XAxis.Scale;////////////////////////////////////1
                Scale yscale12 = zedGraphControl1.GraphPane.YAxis.Scale;

                Scale xscale34 = zedGraphControl2.GraphPane.XAxis.Scale;/////////////////////////////////////2
                Scale yscale34 = zedGraphControl2.GraphPane.YAxis.Scale;

                Scale xscale56 = zedGraphControl3.GraphPane.XAxis.Scale;///////////////////////////////////3
                Scale yscale56 = zedGraphControl3.GraphPane.YAxis.Scale;

                Scale X = zedGraphControl4.GraphPane.XAxis.Scale;//////////////////////////////////////////4
                Scale Y = zedGraphControl4.GraphPane.YAxis.Scale;

                Scale X2 = zedGraphControl4.GraphPane.XAxis.Scale;//////////////////////////////////////////4
                Scale Y2 = zedGraphControl4.GraphPane.YAxis.Scale;

                Scale X3 = zedGraphControl4.GraphPane.XAxis.Scale;//////////////////////////////////////////4
                Scale Y3 = zedGraphControl4.GraphPane.YAxis.Scale;
                // chu kì là 10 ví dụ chu kì đầu tiên 
                // time1 = 0  < 10 - 1 
                // time1 = 1  < 10 - 1
                // ...
                // ...
                // time1 = 10 > 10 - 1 => max = 11 , min = 1
                // time1 = 11 > 11 - 1 => max = 12 , min = 2
                // time1 = 12 > 12 - 1 => max = 13 , min = 3
                // ...
                if (time1 > xscale12.Max - xscale12.MajorStep)/////////////////////////////////////////////////1
                {
                    xscale12.Max = time1 + xscale12.MajorStep;
                    xscale12.Min = xscale12.Max - 5;
                }

                // Nếu giá trị mới lớn hơn giá trị tối đa của trục y, cập nhật trục y
                if (Math.Max(GrapValue1, GrapValue2) > yscale12.Max - yscale12.MajorStep)//////////////////////1
                {
                    yscale12.Max = Math.Max(GrapValue1, GrapValue2) + yscale12.MajorStep;
                    yscale12.Min = yscale12.Max - 5; // Khoảng giữa giá trị tối thiểu và tối đa của trục y là 40
                }






                if (time2 > xscale34.Max - xscale34.MajorStep)/////////////////////////////////////////////////2
                {
                    xscale34.Max = time1 + xscale34.MajorStep;
                    xscale34.Min = xscale34.Max - 5;
                }

                if (Math.Max(GrapValue3, GrapValue4) > yscale34.Max - yscale34.MajorStep)//////////////////////2
                {
                    yscale34.Max = Math.Max(GrapValue3, GrapValue4) + yscale34.MajorStep;
                    yscale34.Min = yscale34.Max - 5; // Khoảng giữa giá trị tối thiểu và tối đa của trục y là 40
                }



                if (time3 > xscale56.Max - xscale56.MajorStep)//////////////////////////////////////////////////3
                {
                    xscale56.Max = time1 + xscale56.MajorStep;
                    xscale56.Min = xscale56.Max - 5;
                }



                if (Math.Max(GrapValue5, GrapValue6) > yscale56.Max - yscale56.MajorStep)//////////////////////3
                {
                    yscale56.Max = Math.Max(GrapValue5, GrapValue6) + yscale56.MajorStep;
                    yscale56.Min = yscale56.Max - 5; // Khoảng giữa giá trị tối thiểu và tối đa của trục y là 40
                }



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                if (GrapValue1 > X.Max - X.MajorStep)///////////////////////////////////////////////////////////4
                {
                    X.Max = GrapValue5 + X.MajorStep;
                    X.Min = X.Max - 1; // Khoảng giữa giá trị tối thiểu và tối đa của trục y là 5
                }

                if (GrapValue2 > Y.Max - Y.MajorStep)///////////////////////////////////////////////////////////4
                {
                    Y.Max = GrapValue6 + Y.MajorStep;
                    Y.Min = Y.Max - 1; // Khoảng giữa giá trị tối thiểu và tối đa của trục y là 5
                }

                if (GrapValue3 > X2.Max - X2.MajorStep)///////////////////////////////////////////////////////////4
                {
                    X2.Max = GrapValue3 + X2.MajorStep;
                    X2.Min = X2.Max - 1; // Khoảng giữa giá trị tối thiểu và tối đa của trục y là 5
                }

                if (GrapValue4 > Y2.Max - Y2.MajorStep)///////////////////////////////////////////////////////////4
                {
                    Y2.Max = GrapValue4 + Y2.MajorStep;
                    Y2.Min = Y2.Max - 1; // Khoảng giữa giá trị tối thiểu và tối đa của trục y là 5
                }

                if (GrapValue5 > X3.Max - X3.MajorStep)///////////////////////////////////////////////////////////4
                {
                    X3.Max = GrapValue5 + X3.MajorStep;
                    X3.Min = X3.Max - 1; // Khoảng giữa giá trị tối thiểu và tối đa của trục y là 5
                }

                if (GrapValue6 > Y3.Max - Y3.MajorStep)///////////////////////////////////////////////////////////4
                {
                    Y3.Max = GrapValue6 + Y3.MajorStep;
                    Y3.Min = Y3.Max - 1; // Khoảng giữa giá trị tối thiểu và tối đa của trục y là 5
                }



                zedGraphControl1.AxisChange();/////////////////////////1
                zedGraphControl1.Invalidate();

                zedGraphControl2.AxisChange();/////////////////////////2
                zedGraphControl2.Invalidate();

                zedGraphControl3.AxisChange();/////////////////////////3
                zedGraphControl3.Invalidate();

                zedGraphControl4.AxisChange();/////////////////////////4
                zedGraphControl4.Invalidate();

            }
        }





        // Khai báo một biến để lưu trữ dữ liệu nhận được từ cổng serial


        private void ProcessBufferData()
        {
            // Kiểm tra xem có dữ liệu trong bộ đệm không
            if (!string.IsNullOrEmpty(bufferData))
            {
                int firstSemicolonIndex  = bufferData.IndexOf(';');//////////////////////////////////////////////////1
                int secondSemicolonIndex = bufferData.IndexOf(';', firstSemicolonIndex  + 1);

                int thirdSemicolonIndex  = bufferData.IndexOf(';', secondSemicolonIndex + 1);/////////////////////////////2
                int fourthSemicolonIndex = bufferData.IndexOf(';', thirdSemicolonIndex  + 1);

                int fifthSemicolonIndex = bufferData.IndexOf(';', fourthSemicolonIndex + 1);///////////////////////////////3
                int sixthSemicolonIndex = bufferData.IndexOf(';', fifthSemicolonIndex + 1);


                // Xử lý dữ liệu trong bộ đệm cho đến khi không còn dấu chấm phẩy nào được tìm thấy
                while (firstSemicolonIndex != -1 && secondSemicolonIndex != -1 && thirdSemicolonIndex != -1 && fourthSemicolonIndex != -1 && fifthSemicolonIndex != -1 && sixthSemicolonIndex != -1)
                {
                    // Lấy giá trị từ đầu chuỗi đến trước dấu chấm phẩy
                    string data1 = bufferData.Substring(0, firstSemicolonIndex);////////////////////////////1
                    string data2 = bufferData.Substring(firstSemicolonIndex  + 1,  secondSemicolonIndex -  firstSemicolonIndex   - 1);

                    string data3 = bufferData.Substring(secondSemicolonIndex + 1, thirdSemicolonIndex   -  secondSemicolonIndex  - 1);///////////////////////////////2
                    string data4 = bufferData.Substring(thirdSemicolonIndex  + 1,  fourthSemicolonIndex -  thirdSemicolonIndex   - 1);

                    string data5 = bufferData.Substring(fourthSemicolonIndex + 1, fifthSemicolonIndex   - fourthSemicolonIndex   - 1);//////////////////////////////3
                    string data6 = bufferData.Substring(fifthSemicolonIndex  + 1,  sixthSemicolonIndex  - fifthSemicolonIndex    - 1);
                    // Thêm giá trị vào listBox hoặc làm gì đó với giá trị đó
                    listBox1.Items.Add(data1);
                    listBox2.Items.Add(data2);

                    listBox3.Items.Add(data3);
                    listBox4.Items.Add(data4);

                    listBox5.Items.Add(data5);
                    listBox6.Items.Add(data6);

                    Draw(data1,data2,data3,data4, data5, data6);

                    
               
                    // Cập nhật lại bộ đệm bằng cách loại bỏ phần đã lấy và dấu chấm phẩy
                    bufferData = bufferData.Substring(sixthSemicolonIndex + 1);

                    // Tìm vị trí của dấu chấm phẩy tiếp theo trong bộ đệm còn lại
                    firstSemicolonIndex = bufferData.IndexOf(';');
                    secondSemicolonIndex = bufferData.IndexOf(';', firstSemicolonIndex  + 1);
                    thirdSemicolonIndex = bufferData.IndexOf(';' , secondSemicolonIndex + 1);
                    fourthSemicolonIndex = bufferData.IndexOf(';', thirdSemicolonIndex  + 1);
                    fifthSemicolonIndex = bufferData.IndexOf(';' , fourthSemicolonIndex + 1);
                    sixthSemicolonIndex = bufferData.IndexOf(';' , fifthSemicolonIndex  + 1);

                }
            }
        }











        ////////////// private void
    }
}



