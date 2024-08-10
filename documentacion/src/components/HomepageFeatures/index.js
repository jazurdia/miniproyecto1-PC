import clsx from 'clsx';
import Heading from '@theme/Heading';
import styles from './styles.module.css';

const FeatureList = [
  {
    title: 'Angel Castellanos',
    Svg: require('@site/static/img/angel.jpg').default,
    description: (
      <>
        Soy un desarrollador destacado y exitoso, que día con día, se desafía a sí mismo a ser mejor, con el fin de desarrollar mis conocimientos actuales y de adquirir nuevos, para así poder mejorar no solo mi futuro sino también el de mi país.
      </>
    ),
  },
  {
    title: 'Alejandro Azrudia',
    Svg: require('@site/static/img/azurdia.png').default,
    description: (
      <>
        Soy un joven responsable, eficiente, discreto y confiable. Enfocado en la resolución de problemas, trabajo en equipo y bajo presión. Me destaco por mi pensamiento crítico, analítico, habilidades técnicas y comunicacionales. Tengo una amplia disposición al aprendizaje continuo y gusto por acrecentar mi cultura general.
      </>
    ),
  },
  {
    title: 'Diego Morales',
    Svg: require('@site/static/img/paralelasLogo.png').default,
    description: (
      <>
        Es regay
      </>
    ),
  },
];

function Feature({Svg, title, description}) {
  return (
    <div className={clsx('col col--4')}>
      <div className="text--center">
        <img src={Svg} className={styles.featureSvg} role="img" style={{borderRadius: "50%"}}/>
      </div>
      <div className="text--center padding-horiz--md">
        <Heading as="h3">{title}</Heading>
        <p>{description}</p>
      </div>
    </div>
  );
}

export default function HomepageFeatures() {
  return (
    <section className={styles.features}>
      <div className="container">
        <div className="row">
          {FeatureList.map((props, idx) => (
            <Feature key={idx} {...props} />
          ))}
        </div>
      </div>
    </section>
  );
}
