uint16_t sample_voltage;

void test()
{
    while(1)
    {
        sample_voltage = do_ADC();
        Disp2Hex(sample_voltage);
        Disp2String('\n');
        // Only 
    }
}
