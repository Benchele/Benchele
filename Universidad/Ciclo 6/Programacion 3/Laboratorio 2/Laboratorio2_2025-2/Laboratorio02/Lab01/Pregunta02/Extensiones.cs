using Lab01.Pregunta01;
namespace Lab01.Pregunta02
{
    public static class ExtensionesDeICotizable
    {
        public static ICotizable ConCoberturaContraRobos(this ICotizable cotizable)
        {
            return new CoberturaContraRobos(cotizable);
        }
        public static ICotizable ConAsistenciaVial(this ICotizable cotizable)
        {
            return new CoberturaAsistenciaVial(cotizable);
        }
        public static ICotizable ConCoberturaContraDesastresNaturales(this ICotizable cotizable)
        {
            return new CoberturaContraDesastresNaturales(cotizable);
        }
    }
}
